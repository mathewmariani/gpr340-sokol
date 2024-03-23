// engine
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "libs/imgui/imgui.h"

// generators
#include "generators/mazegenerator.h"
#include "generators/huntandkill.h"
#include "generators/randomwalk.h"
#include "generators/recursivebacktracker.h"

#include "world.h"

#include <vector>
#include <memory>

static struct
{
  struct
  {
    bool is_simulating = false;
    float accumulated_time = 0.0f;
    float tick_rate = 0.31415f;
  } simulator;

  struct
  {
    int rule_index = 0;
    int current_size = 5;
  } demo;

  struct
  {
    int x;
    int y;
  } camera;

  World world;
  std::vector<std::unique_ptr<MazeGenerator>> generators;
} state;

namespace maze
{
  static void step()
  {
    auto *generator = state.generators[state.demo.rule_index].get();
    if (!generator->Step(state.world))
    {
      state.simulator.is_simulating = false;
    }
  }

  static void clear()
  {
    state.simulator.is_simulating = false;
    state.world.Resize(state.demo.current_size);

    auto *generator = state.generators[state.demo.rule_index].get();
    generator->Clear(state.world);
  }
}

static void load(void)
{
  /* initialize rules */
  state.generators.push_back(std::unique_ptr<HuntAndKill>(new HuntAndKill()));
  state.generators.push_back(std::unique_ptr<RandomWalk>(new RandomWalk()));
  state.generators.push_back(std::unique_ptr<RecursiveBacktracker>(new RecursiveBacktracker()));

  maze::clear();
}

static void cleanup(void)
{
  state.generators.clear();
}

static void update(float dt)
{
  if (state.simulator.is_simulating)
  {
    state.simulator.accumulated_time += dt;
    if (state.simulator.accumulated_time > state.simulator.tick_rate)
    {
      maze::step();
      state.simulator.accumulated_time = 0;
    }
  }
}

static void draw(void)
{
  int width, height;
  engine::graphics::get_dimensions(&width, &height);

  state.camera.x = (width - (state.demo.current_size * 16)) * 0.5f;
  state.camera.y = (height - (state.demo.current_size * 16)) * 0.5f;

  /* keep camera focused on the grid */
  engine::graphics::push_transform();
  engine::graphics::translate(state.camera.x, state.camera.y);

  /* draw nodes */
  state.world.Render();

  /* pop the camera */
  engine::graphics::pop_transform();
}

static void gui()
{
  ImGui::Begin("Controlls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS", ImGui::GetIO().DeltaTime * 1000, 1.0f / ImGui::GetIO().DeltaTime, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  /* simulator */
  ImGui::Separator();
  ImGui::Text("Simulation");
  ImGui::Separator();
  ImGui::SliderFloat("Tick Rate", &state.simulator.tick_rate, 0.0001f, 1.0f);
  if (ImGui::Button("Step"))
  {
    state.simulator.is_simulating = false;
    state.simulator.accumulated_time += ImGui::GetIO().DeltaTime;
    maze::step();
  }
  ImGui::SameLine();
  if (ImGui::Button("Start"))
  {
    state.simulator.is_simulating = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("Pause"))
  {
    state.simulator.is_simulating = false;
  }
  ImGui::SameLine();
  if (ImGui::Button("Clear"))
  {
    maze::clear();
  }

  ImGui::Separator();
  ImGui::Text("Maze Generator");
  ImGui::Separator();
  auto new_width = state.demo.current_size;
  if (ImGui::SliderInt("Width", &new_width, 5, 49))
  {
    /* width should always be even */
    new_width = (2 * new_width) / 2;
    if (new_width != state.demo.current_size)
    {
      state.demo.current_size = new_width;
      state.world.Resize(new_width);
    }
  }
  if (ImGui::BeginCombo("Generator", state.generators[state.demo.rule_index]->GetName().c_str()))
  {
    for (auto n = 0; n < state.generators.size(); ++n)
    {
      auto is_selected = (state.generators[state.demo.rule_index]->GetName() == state.generators[n]->GetName());
      if (ImGui::Selectable(state.generators[n]->GetName().c_str(), is_selected))
      {
        state.demo.rule_index = n;
        maze::clear();
      }
      if (is_selected)
      {
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }

  ImGui::End();
}

game_desc game_main(int argv, char *argc[])
{
  game_desc desc{
      .load_cb = load,
      .cleanup_cb = cleanup,
      .update_cb = update,
      .draw_cb = draw,
      .gui_cb = gui,
      .config = {
          .window = {
              .title = "Maze",
              .width = 800,
              .height = 800,
          },
      },
  };
  return desc;
}