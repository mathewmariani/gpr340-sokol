/* engine */
#include "math/math.h"
#include "graphics/graphics.h"

#include "agents/cat.h"
#include "agents/catcher.h"

#include "world.h"

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

void World::Resize(int new_size)
{
  grid.clear();
  grid.resize(new_size);
}

void World::Render()
{
  const auto dynamic_size = (800.0f / (grid.get_radius() * 2 + 1)) * 0.5;
  auto hx = 0.0f;
  auto hy = 0.0f;
  for (const auto hex : grid)
  {
    grid.hex_to_pixel(layout_flat, hex.first, dynamic_size, &hx, &hy);
    engine::graphics::set_color(1.0f, 1.0f, 1.0f, 1.0f);
    engine::graphics::hexagon(engine::graphics::DrawMode::DRAW_MODE_LINE, false, hx, hy, dynamic_size);
  }
}