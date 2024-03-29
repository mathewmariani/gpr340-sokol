/* engine */
#include "graphics/graphics.h"
#include "math/math.h"
#include "common/color.h"

#include "world.h"

namespace
{
  const static Colorf alive_color = LightYellow;
  const static Colorf dead_color = DarkSlateGray;
}

static inline void wrap(int size, int &x, int &y)
{
  if (x < 0)
  {
    x += size;
  }
  else if (x >= size)
  {
    x %= size;
  }
  if (y < 0)
  {
    y += size;
  }
  else if (y >= size)
  {
    y %= size;
  }
}

void World::Resize(int new_width)
{
  buffer_index = 0;
  size = new_width;
  for (auto i = 0; i < 2; ++i)
  {
    buffer[i].clear();
    buffer[i].resize(new_width);
  }
}

void World::Randomize(float chance)
{
  for (auto y = 0; y < size; ++y)
  {
    for (auto x = 0; x < size; ++x)
    {
      auto rand = engine::math::random(0.0f, 1.0f);
      auto is_alive = (rand < chance) ? true : false;
      buffer[buffer_index].at({x, y}).value = is_alive;
    }
  }
}

void World::SwapBuffers()
{
  buffer_index = (buffer_index + 1) % 2;
  buffer[(buffer_index + 1) % 2] = buffer[buffer_index];
}

int World::GetNeighbourhood(int x, int y) const
{
  wrap(size, x, y);
  return buffer[buffer_index % 2].neighbors({x, y}).size();
}

Cell World::Get(int x, int y) const
{
  wrap(size, x, y);
  return buffer[buffer_index % 2].at({x, y});
}

void World::Set(int x, int y, const Cell &value)
{
  wrap(size, x, y);
  buffer[buffer_index % 2].at({x, y}) = value;
}

void World::SetNext(int x, int y, const Cell &value)
{
  wrap(size, x, y);
  buffer[buffer_index + 1].at({x, y}) = value;
}

void World::Render()
{
  /* draw nodes */
  for (auto j = 0; j < Size(); ++j)
  {
    for (auto i = 0; i < Size(); ++i)
    {
      auto color = Get(i, j).value ? alive_color : dead_color;
      engine::graphics::set_color(color);
      engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, i * 16, j * 16, 16, 16);
    }
  }
}