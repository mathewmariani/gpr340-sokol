/* engine */
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "mouse/mouse.h"
#include "imgui/imgui.h"

/* rules */
#include "rules/rulebase.h"
#include "rules/cavegeneration.h"
#include "rules/johnconway.h"
#include "rules/langtonsant.h"

#include "world.h"

#include <memory>

namespace
{
  constexpr float tile_size = 16.0f;
}

static struct
{
  struct
  {
    bool is_simulating = false;
    float accumulated_time = 0.0f;
    float tick_rate = 0.123f;
  } simulator;

  struct
  {
    int x;
    int y;
  } camera;

  struct
  {
    int rule_index = 0;
    int current_size = 5;
    float random_chance = 0.4f;
    bool painting = false;
  } demo;

  World world;
  std::vector<std::unique_ptr<RuleBase>> rules;
} state;

namespace cellular_automata
{
  static void step()
  {
    auto *rule = state.rules[state.demo.rule_index].get();
    rule->Step(state.world);
    state.world.SwapBuffers();
  }

  static void clear()
  {
    state.simulator.is_simulating = false;
    state.world.Resize(state.demo.current_size);
  }
}

static void load(void)
{
  /* initialize rules */
  state.rules.push_back(std::unique_ptr<JohnConway>(new JohnConway()));
  state.rules.push_back(std::unique_ptr<CaveGeneration>(new CaveGeneration()));
  state.rules.push_back(std::unique_ptr<LangtonsAnt>(new LangtonsAnt()));

  cellular_automata::clear();
}

static void cleanup(void)
{
  state.rules.clear();
}

static void update(float dt)
{
  if (state.simulator.is_simulating)
  {
    state.simulator.accumulated_time += dt;
    if (state.simulator.accumulated_time > state.simulator.tick_rate)
    {
      cellular_automata::step();
      state.simulator.accumulated_time = 0;
    }
  }
}

static void draw(void)
{
  int width, height;
  engine::graphics::get_dimensions(&width, &height);
  state.camera.x = (width - (state.demo.current_size * tile_size)) * 0.5f;
  state.camera.y = (height - (state.demo.current_size * tile_size)) * 0.5f;

  /* keep camera focused on the grid */
  engine::graphics::push_transform();
  engine::graphics::translate(state.camera.x, state.camera.y);

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
    cellular_automata::step();
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
    cellular_automata::clear();
  }

  ImGui::Separator();
  ImGui::Text("Grid");
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

  // ImGui::ColorEdit3("Alive Color", &state.light.color.X, ImGuiColorEditFlags_None);
  // ImGui::ColorEdit3("Dead Color", &state.light.color.X, ImGuiColorEditFlags_None);

  ImGui::SliderFloat("Randomness", &state.demo.random_chance, 0.01f, 1.0f);
  if (ImGui::Button("Randomize"))
  {
    state.simulator.is_simulating = false;
    state.world.Randomize(state.demo.random_chance);
  }

  ImGui::Separator();
  ImGui::Text("Ruleset");
  ImGui::Separator();
  if (ImGui::BeginCombo("##combo_Rulesets", state.rules[state.demo.rule_index]->GetName().c_str()))
  {
    for (auto n = 0; n < state.rules.size(); ++n)
    {
      auto is_selected = (state.rules[state.demo.rule_index]->GetName() == state.rules[n]->GetName());
      if (ImGui::Selectable(state.rules[n]->GetName().c_str(), is_selected))
      {
        state.demo.rule_index = n;
        cellular_automata::clear();
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

static void mouse_pressed(float x, float y, int button)
{
  const auto width = state.world.Size();

  x -= state.camera.x;
  y -= state.camera.y;

  int i = (x / tile_size);
  int j = (y / tile_size);

  if ((i >= 0 && i < width) && (j >= 0 && j < width))
  {
    state.demo.painting = !state.world.Get(i, j).value;
    state.world.Set(i, j, state.demo.painting);
  }
}

static void mouse_moved(float x, float y, float dx, float dy)
{
  if (engine::mouse::is_down())
  {
    const auto width = state.world.Size();

    x -= state.camera.x;
    y -= state.camera.y;

    int i = (x / tile_size);
    int j = (y / tile_size);

    if ((i >= 0 && i < width) && (j >= 0 && j < width))
    {
      state.world.Set(i, j, {state.demo.painting});
    }
  }
}

game_desc game_main(int argv, char *argc[])
{
  game_desc desc{
      .load_cb = load,
      .cleanup_cb = cleanup,
      .update_cb = update,
      .draw_cb = draw,
      .gui_cb = gui,
      .mouse_pressed_cb = mouse_pressed,
      .mouse_moved_cb = mouse_moved,
      .config = {
          .window = {
              .title = "Cellular Automata",
              .width = 800,
              .height = 800,
          },
      },
  };
  return desc;
}