// engine
#include "engine/engine.h"
#include "mouse/mouse.h"
#include "graphics/graphics.h"
#include "imgui/imgui.h"

#include "pathfinding.h"

#include "batteries/grid_world.h"

#include <vector>
#include <memory>

int tile_size = 16;

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
    int current_size = 30;
  } demo;

  struct
  {
    int x;
    int y;
  } camera;

  struct
  {
    bool is_drag = false;
    float x = 0.0f;
    float y = 0.0f;
  } mouse;

  std::vector<batteries::grid_location<int>> path;
} state;

batteries::grid_location<int> start{0, 0};
batteries::grid_location<int> goal{16, 16};
batteries::grid_world world{30, 30};
int step_limit = 10;
bool redraw = true;

// using SearchFunction = std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> (*)(const World &, const batteries::grid_location<int> &, int);
// struct MapEntry
// {
//   std::string name;
//   SearchFunction fn;
// };
// std::vector<MapEntry> search_algorithms{
//     {"AStarSearch", Pathfinding::AStarSearch},
//     {"BreadthFirstSearch", Pathfinding::BreadthFirstSearch},
//     {"DijkstraSearch", Pathfinding::DijkstraSearch},
//     {"GreedySearch", Pathfinding::GreedySearch},
// };

// inline batteries::grid_location<int> mouse_to_tile(float x, float y)
// {
//   int width, height;
//   engine::graphics::get_dimensions(&width, &height);
//   x -= state.camera.x;
//   y -= state.camera.y;
//   const auto size = 16; //(800.0f / (grid.get_radius() * 2 + 1)) * 0.5;
//   auto fractional_tile = batteries::finite_grid<NodeType>::pixel_to_tile(size, x, y);
//   return batteries::finite_grid<NodeType>::tile_round(fractional_tile);
// }

namespace maze
{
  static void step()
  {
  }

  static void clear()
  {
  }
}

static void load(void)
{
  maze::clear();
  engine::mouse::set_cursor(engine::mouse::mouse_cursor::MOUSECURSOR_POINTING_HAND);
}

static void cleanup(void)
{
}

static void update(float dt)
{
  if (state.simulator.is_simulating)
  {
    state.simulator.accumulated_time += dt;
    if (state.simulator.accumulated_time > state.simulator.tick_rate)
    {
      state.simulator.accumulated_time = 0;
      maze::step();
    }
  }

  // it costs nothing, just reconstruct every frame.
  // state.path = Pathfinding::ConstructPath(t.second, start, goal);

  auto pf = Pathfinding::BreadthFirstSearch(world, start, step_limit);
}

static void draw(void)
{
  // int width, height;
  // engine::graphics::get_dimensions(&width, &height);

  // state.camera.x = (width - (state.demo.current_size * 16)) * 0.5f;
  // state.camera.y = (height - (state.demo.current_size * 16)) * 0.5f;

  // /* keep camera focused on the grid */
  // engine::graphics::push_transform();
  // engine::graphics::translate(state.camera.x, state.camera.y);

  // auto pf = Pathfinding::BreadthFirstSearch(world, start, step_limit);

  // for (const auto t : pf.second)
  // {
  //   engine::graphics::set_color(Beige);
  //   engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, t.first.x * 16, t.first.y * 16, 16, 16);
  // }

  // for (const auto t : pf.first)
  // {
  //   engine::graphics::set_color(CornflowerBlue);
  //   engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_LINE, t.x * 16, t.y * 16, 16, 16);
  // }

  // for (const auto t : state.path)
  // {
  //   engine::graphics::set_color(Purple);
  //   engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, t.x * 16, t.y * 16, 16, 16);
  // }

  // /* draw start and goal */
  // engine::graphics::set_color(Green);
  // engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, start.x * 16, start.y * 16, 16, 16);
  // engine::graphics::set_color(Red);
  // engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, goal.x * 16, goal.y * 16, 16, 16);

  // /* pop the camera */
  // engine::graphics::pop_transform();
}

static void gui()
{
  ImGui::Begin("Controlls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS", ImGui::GetIO().DeltaTime * 1000, 1.0f / ImGui::GetIO().DeltaTime, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  ImGui::Separator();
  ImGui::Text("Search Algorithm");
  ImGui::Separator();

  ImGui::Separator();
  redraw |= ImGui::SliderInt("Step Limit", &step_limit, 0, 900);
  ImGui::SliderInt("Start Position (x)", &start.x, 0, 30 - 1);
  ImGui::SliderInt("Start Position (y)", &start.y, 0, 30 - 1);
  ImGui::SliderInt("Goal Position (x)", &goal.x, 0, 30 - 1);
  ImGui::SliderInt("Goal Position (y)", &goal.y, 0, 30 - 1);
  ImGui::Separator();

  ImGui::End();
}

static void mouse_pressed(float x, float y, int button)
{
}

static void mouse_released(float x, float y, int button)
{
  state.mouse.is_drag = false;
}

static void mouse_moved(float x, float y, float dx, float dy)
{
}

game_desc game_main(int argv, char *argc[])
{
  game_desc desc{
      .load_cb = load,
      .cleanup_cb = cleanup,
      .update_cb = update,
      .draw_cb = draw,
      .gui_cb = gui,
      .mouse_moved_cb = mouse_moved,
      .mouse_pressed_cb = mouse_pressed,
      .mouse_released_cb = mouse_released,
      .config = {
          .window = {
              .title = "Tower Defense",
              .width = 800,
              .height = 800,
          },
      },
  };
  return desc;
}