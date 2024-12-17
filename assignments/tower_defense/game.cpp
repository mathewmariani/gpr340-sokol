// engine
#include "engine/engine.h"
#include "mouse/mouse.h"
#include "graphics/graphics.h"
#include "imgui/imgui.h"

// search
#include "search/astarsearch.h"
#include "search/breadthfirstsearch.h"
#include "search/dijkstrasearch.h"
#include "search/greedysearch.h"
#include "search/search.h"

#include "world.h"

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
    NodeType painting = NodeType::Wall;
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

  World world;
  std::vector<std::unique_ptr<Search>> searchers;
} state;

inline batteries::grid_location<int> mouse_to_tile(float x, float y)
{
  int width, height;
  engine::graphics::get_dimensions(&width, &height);

  x -= state.camera.x;
  y -= state.camera.y;

  const auto size = 16; //(800.0f / (grid.get_radius() * 2 + 1)) * 0.5;
  auto fractional_tile = batteries::finite_grid<Node>::pixel_to_tile(size, x, y);

  return batteries::finite_grid<Node>::tile_round(fractional_tile);
}

namespace maze
{
  static void step()
  {
    // auto *solver = state.searchers[state.demo.rule_index].get();
    // if (!solver->Step(state.world))
    // {
    //   state.simulator.is_simulating = false;
    // }
  }

  static void clear()
  {
    state.simulator.is_simulating = false;
    state.world.Resize(state.demo.current_size);
    auto *solver = state.searchers[state.demo.rule_index].get();
  }
}

static void load(void)
{
  /* initialize searchers */
  state.searchers.push_back(std::unique_ptr<AStarSearch>(new AStarSearch()));
  state.searchers.push_back(std::unique_ptr<DijkstraSearch>(new DijkstraSearch()));
  state.searchers.push_back(std::unique_ptr<BreadthFirstSearch>(new BreadthFirstSearch()));
  state.searchers.push_back(std::unique_ptr<GreedySearch>(new GreedySearch()));

  maze::clear();

  engine::mouse::set_cursor(engine::mouse::mouse_cursor::MOUSECURSOR_POINTING_HAND);
}

static void cleanup(void)
{
  state.searchers.clear();
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

  if (state.mouse.is_drag)
  {
    auto curr_tile = mouse_to_tile(state.mouse.x, state.mouse.y);
    auto *start = state.world.GetStart();
    if (curr_tile == *start)
    {
      *start = curr_tile;
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

  // auto *searcher = state.searchers[state.demo.rule_index].get();
  // searcher->Render();

  auto x = engine::mouse::get_x();
  auto y = engine::mouse::get_y();
  auto t = mouse_to_tile(x, y);

  engine::graphics::set_color(CornflowerBlue);
  engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, t.x * 16, t.y * 16, 16, 16);

  /* pop the camera */
  engine::graphics::pop_transform();
}

static void gui()
{
  ImGui::Begin("Controlls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS", ImGui::GetIO().DeltaTime * 1000, 1.0f / ImGui::GetIO().DeltaTime, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  auto x = engine::mouse::get_x();
  auto y = engine::mouse::get_y();
  auto t = mouse_to_tile(x, y);
  ImGui::Text("%d, %d", t.x, t.y);

  ImGui::Separator();
  ImGui::Text("Search Algorithm");
  ImGui::Separator();
  if (ImGui::BeginCombo("searchers", state.searchers[state.demo.rule_index]->GetName().c_str()))
  {
    for (auto n = 0; n < state.searchers.size(); ++n)
    {
      auto is_selected = (state.searchers[state.demo.rule_index]->GetName() == state.searchers[n]->GetName());
      if (ImGui::Selectable(state.searchers[n]->GetName().c_str(), is_selected))
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
  if (ImGui::BeginCombo("Search", state.searchers[state.demo.rule_index]->GetName().c_str()))
  {
    for (auto n = 0; n < state.searchers.size(); ++n)
    {
      auto is_selected = (state.searchers[state.demo.rule_index]->GetName() == state.searchers[n]->GetName());
      if (ImGui::Selectable(state.searchers[n]->GetName().c_str(), is_selected))
      {
        state.demo.rule_index = n;
        state.searchers[n].get()->Find(state.world, *state.world.GetStart());
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

static void mouse_pressed(float x, float y, int button)
{
}

static void mouse_released(float x, float y, int button)
{
  state.mouse.is_drag = false;
}

static void mouse_moved(float x, float y, float dx, float dy)
{
  if (engine::mouse::is_down())
  {
    state.mouse.is_drag = true;
    state.mouse.x = x;
    state.mouse.y = y;
  }
  // switch (type)
  // {
  // case NodeType::Empty:
  //   // TODO: painting empty
  //   printf("painting empty\n");
  //   break;
  // case NodeType::Wall:
  //   // TODO: painting wall
  //   printf("painting wall\n");
  //   break;
  // case NodeType::Start:
  //   // TODO: dragging player
  //   printf("dragging player\n");
  //   break;
  // case NodeType::Goal:
  //   // TODO: dragging enemy
  //   printf("dragging enemy\n");
  //   break;
  // default:
  //   printf("default\n");
  //   break;
  // }
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