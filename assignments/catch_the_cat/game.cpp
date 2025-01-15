/* engine */
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "mouse/mouse.h"
#include "imgui/imgui.h"

#include "world.h"

#include "agents/cat.h"
#include "agents/catcher.h"

struct
{
  struct
  {
    bool is_simulating = false;
    float accumulated_time = 0.0f;
    float tick_rate = 0.31415f;
  } simulator;

  struct
  {
    bool pointy = true;
    bool shifted = true;
    int current_size = 5;
  } demo;

  struct
  {
    float x = 0.0f;
    float y = 0.0f;
  } camera;

  // Cat cat;
  // Catcher catcher;
  batteries::hexgrid<bool> grid;
  World world;
} state;

namespace catch_the_cat
{
  static void step()
  {
    // TODO: implementation.
    // auto *generator = state.generators[state.demo.rule_index].get();
    // if (!generator->Step(state.world))
    // {
    //   state.simulator.is_simulating = false;
    // }
  }

  static void clear()
  {
    state.simulator.is_simulating = false;
    state.world.Resize(state.demo.current_size);

    // TODO: implementation.
    // auto *generator = state.generators[state.demo.rule_index].get();
    // generator->Clear(state.world);
  }
}

static void load(void)
{
  catch_the_cat::clear();
}

static void cleanup(void)
{
  catch_the_cat::clear();
}

static void update(float dt)
{
  if (state.simulator.is_simulating)
  {
    state.simulator.accumulated_time += dt;
    if (state.simulator.accumulated_time > state.simulator.tick_rate)
    {
      catch_the_cat::step();
      state.simulator.accumulated_time = 0;
    }
  }
}

static void draw(void)
{
  int width, height;
  engine::graphics::get_dimensions(&width, &height);

  /* keep camera focused on the grid */
  engine::graphics::push_transform();
  engine::graphics::translate(width * 0.5f, width * 0.5f);

  state.world.Render();

  engine::graphics::pop_transform();
}

static void gui()
{
  ImGui::Begin("Controlls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS", ImGui::GetIO().DeltaTime * 1000, 1.0f / ImGui::GetIO().DeltaTime, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  // ImGui::Text("Hexagon");
  // if (ImGui::Checkbox("Pointy", &state.demo.pointy))
  // {
  //   state.layout = state.demo.pointy ? layout_pointy : layout_flat;
  // }

  ImGui::Text("Grid");
  if (ImGui::SliderInt("##slider_current_size", &state.demo.current_size, 5, 50))
  {
    state.world.Resize(state.demo.current_size);
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
              .title = "Catch the Cat",
              .width = 800,
              .height = 800,
          },
      },
  };
  return desc;
}