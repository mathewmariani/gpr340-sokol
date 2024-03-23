#include "cavegeneration.h"

namespace
{
  enum
  {
    AIR = 0,
    ROCK = 1,
  };
}

void CaveGeneration::Step(World &world)
{
  int n;
  bool is_alive;
  for (auto j = 0; j < world.Size(); ++j)
  {
    for (auto i = 0; i < world.Size(); ++i)
    {
      is_alive = world.Get(i, j).value;
      n = CountNeighbors(world, i, j);

      if (is_alive)
      {
        world.SetNext(i, j, {(uint8_t)((n < 3) ? ROCK : AIR)});
      }
      else
      {
        world.SetNext(i, j, {(uint8_t)((n > 4) ? AIR : ROCK)});
      }
    }
  }

  /* always last */
  world.SwapBuffers();
}

int CaveGeneration::CountNeighbors(const World &world, int x, int y) const
{
  auto count = 0;

  /* moores neighborhood */
  count += world.Get(x - 1, y - 1).value ? 1 : 0;
  count += world.Get(x + 0, y - 1).value ? 1 : 0;
  count += world.Get(x + 1, y - 1).value ? 1 : 0;
  count += world.Get(x - 1, y + 0).value ? 1 : 0;
  count += world.Get(x + 1, y + 0).value ? 1 : 0;
  count += world.Get(x - 1, y + 1).value ? 1 : 0;
  count += world.Get(x + 0, y + 1).value ? 1 : 0;
  count += world.Get(x + 1, y + 1).value ? 1 : 0;

  return count;
}
