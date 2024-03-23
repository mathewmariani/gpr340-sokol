/* engine */
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "mouse/mouse.h"
#include "imgui/imgui.h"

/* batteries */
#include "batteries/hexgrid.h"

#define STUBBED() \
  std::printf("[%s]\n", __FUNCTION__)

namespace engine
{
  namespace graphics
  {
    /* FIXME: this is a sloppy algorithm. */
    static void hexagon(DrawMode mode, bool pointy, float x, float y, float size)
    {
      if (pointy)
      {
        if (mode == DrawMode::DRAW_MODE_FILL)
        {
          Vector2f vertices[]{
              {x + size * std::sinf(3 * ENGINE_PI / 3), y + size * std::cosf(3 * ENGINE_PI / 3)},
              {x + size * std::sinf(2 * ENGINE_PI / 3), y + size * std::cosf(2 * ENGINE_PI / 3)},
              {x + size * std::sinf(4 * ENGINE_PI / 3), y + size * std::cosf(4 * ENGINE_PI / 3)},
              {x + size * std::sinf(1 * ENGINE_PI / 3), y + size * std::cosf(1 * ENGINE_PI / 3)},
              {x + size * std::sinf(5 * ENGINE_PI / 3), y + size * std::cosf(5 * ENGINE_PI / 3)},
              {x + size * std::sinf(0 * ENGINE_PI / 3), y + size * std::cosf(0 * ENGINE_PI / 3)},
          };
          engine::graphics::polygon(engine::graphics::DrawMode::DRAW_MODE_FILL, &vertices[0], 6);
        }
        else
        {
          Vector2f vertices[]{
              {x + size * std::sinf(0 * ENGINE_PI / 3), y + size * std::cosf(0 * ENGINE_PI / 3)},
              {x + size * std::sinf(1 * ENGINE_PI / 3), y + size * std::cosf(1 * ENGINE_PI / 3)},
              {x + size * std::sinf(2 * ENGINE_PI / 3), y + size * std::cosf(2 * ENGINE_PI / 3)},
              {x + size * std::sinf(3 * ENGINE_PI / 3), y + size * std::cosf(3 * ENGINE_PI / 3)},
              {x + size * std::sinf(4 * ENGINE_PI / 3), y + size * std::cosf(4 * ENGINE_PI / 3)},
              {x + size * std::sinf(5 * ENGINE_PI / 3), y + size * std::cosf(5 * ENGINE_PI / 3)},
              {x + size * std::sinf(0 * ENGINE_PI / 3), y + size * std::cosf(0 * ENGINE_PI / 3)},
          };
          engine::graphics::polyline(&vertices[0], 7);
        }
      }
      else
      {
        if (mode == DrawMode::DRAW_MODE_FILL)
        {
          Vector2f vertices[]{
              {x + size * std::cosf(3 * ENGINE_PI / 3), y + size * std::sinf(3 * ENGINE_PI / 3)},
              {x + size * std::cosf(2 * ENGINE_PI / 3), y + size * std::sinf(2 * ENGINE_PI / 3)},
              {x + size * std::cosf(4 * ENGINE_PI / 3), y + size * std::sinf(4 * ENGINE_PI / 3)},
              {x + size * std::cosf(1 * ENGINE_PI / 3), y + size * std::sinf(1 * ENGINE_PI / 3)},
              {x + size * std::cosf(5 * ENGINE_PI / 3), y + size * std::sinf(5 * ENGINE_PI / 3)},
              {x + size * std::cosf(0 * ENGINE_PI / 3), y + size * std::sinf(0 * ENGINE_PI / 3)},
          };
          engine::graphics::polygon(engine::graphics::DrawMode::DRAW_MODE_FILL, &vertices[0], 6);
        }
        else
        {
          Vector2f vertices[]{
              {x + size * std::cosf(0 * ENGINE_PI / 3), y + size * std::sinf(0 * ENGINE_PI / 3)},
              {x + size * std::cosf(1 * ENGINE_PI / 3), y + size * std::sinf(1 * ENGINE_PI / 3)},
              {x + size * std::cosf(2 * ENGINE_PI / 3), y + size * std::sinf(2 * ENGINE_PI / 3)},
              {x + size * std::cosf(3 * ENGINE_PI / 3), y + size * std::sinf(3 * ENGINE_PI / 3)},
              {x + size * std::cosf(4 * ENGINE_PI / 3), y + size * std::sinf(4 * ENGINE_PI / 3)},
              {x + size * std::cosf(5 * ENGINE_PI / 3), y + size * std::sinf(5 * ENGINE_PI / 3)},
              {x + size * std::cosf(0 * ENGINE_PI / 3), y + size * std::sinf(0 * ENGINE_PI / 3)},
          };
          engine::graphics::polyline(&vertices[0], 7);
        }
      }
    }
  }
}

namespace
{
  constexpr engine::graphics::DrawMode line = engine::graphics::DrawMode::DRAW_MODE_LINE;
  constexpr engine::graphics::DrawMode fill = engine::graphics::DrawMode::DRAW_MODE_FILL;
}

namespace
{
  struct
  {
    bool pointy = true;
    bool shifted = true;
    int grid_size = 5;

    struct
    {
      float x = 0.0f;
      float y = 0.0f;
    } camera;

    HexOrientation layout = layout_pointy;
    Hex<int> current_hex{0, 0, 0};
  } state;

  Hexgrid<bool> grid(5);
}

static void load(void);
static void cleanup(void);
static void update(float);
static void draw(void);
static void gui(void);

static void mouse_moved(float, float, float, float);

inline Hex<int> mouse_to_hex(float x, float y)
{
  const auto size = (800.0f / (grid.get_radius() * 2 + 1)) * 0.5;
  auto fractional_hex = Hexgrid<int>::pixel_to_hex(state.layout, size, x - 400, y - 400);

  return Hexgrid<int>::hex_round(fractional_hex);
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
      .config = {
          .window = {
              .title = "Hexagons",
              .width = 800,
              .height = 800,
          },
      },
  };
  return desc;
}
static void load(void)
{
  STUBBED();
}
static void cleanup(void)
{
  STUBBED();
}
static void update(float dt)
{
}
static void draw(void)
{
  /* keep camera focused on the grid */
  engine::graphics::push_transform();
  engine::graphics::translate(400, 400);

  const auto dynamic_size = (800.0f / (grid.get_radius() * 2 + 1)) * 0.5;
  auto hx = 0.0f;
  auto hy = 0.0f;
  for (const auto hex : grid)
  {
    grid.hex_to_pixel(state.layout, hex.first, dynamic_size, &hx, &hy);

    auto mode = (hex.first == state.current_hex) ? fill : line;
    engine::graphics::set_color(1.0f, 1.0f, 1.0f, 1.0f);
    engine::graphics::hexagon(mode, state.pointy, hx, hy, dynamic_size);
  }

  /* draw a circle on current hex */
  auto mouse_x = engine::mouse::get_x();
  auto mouse_y = engine::mouse::get_y();

  auto vector = grid.pixel_to_hex(state.layout, dynamic_size, mouse_x - 400, mouse_y - 400);
  auto curr_hex = grid.hex_round(vector);

  engine::graphics::pop_transform();
}
static void gui()
{
  ImGui::Begin("Settings", nullptr);

  ImGui::Text("Hexagon");
  if (ImGui::Checkbox("Pointy", &state.pointy))
  {
    state.layout = state.pointy ? layout_pointy : layout_flat;
  }

  ImGui::Text("Grid");
  if (ImGui::SliderInt("##slider_grid_size", &state.grid_size, 5, 50))
  {
    grid.resize(state.grid_size);
  }

  ImGui::End();
}

static void mouse_moved(float x, float y, float dx, float dy)
{
  const auto dynamic_size = (800.0f / (grid.get_radius() * 2 + 1)) * 0.5;
  auto vector = grid.pixel_to_hex(state.layout, dynamic_size, x - 400, y - 400);

  auto next_hex = mouse_to_hex(x, y);
  if (grid.contains(next_hex))
  {
    if (state.current_hex != next_hex)
    {
      state.current_hex = next_hex;
    }
  }
}