#include "johnconway.h"

#define CONCISE_RULESET

namespace
{
  enum
  {
    DEAD = 0,
    ALIVE = 1,
  };
}

void JohnConway::Step(World &world)
{
  int n;
  bool is_alive;
  for (auto j = 0; j < world.Size(); ++j)
  {
    for (auto i = 0; i < world.Size(); ++i)
    {
      is_alive = world.Get(i, j).value;
      n = CountNeighbors(world, i, j);

#if defined(CONCISE_RULESET)
      // Any live cell with two or three live neighbours survives.
      // Any dead cell with three live neighbours becomes a live cell.
      // All other live cells die in the next generation. Similarly, all other dead cells stay dead.
      if (is_alive && ((n == 2) || (n == 3)))
      {
        world.SetNext(i, j, {(uint8_t)ALIVE});
      }
      else if (!is_alive && (n == 3))
      {
        world.SetNext(i, j, {(uint8_t)ALIVE});
      }
      else
      {
        world.SetNext(i, j, {(uint8_t)DEAD});
      }
#else
      // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
      // Any live cell with two or three live neighbours lives on to the next generation.
      // Any live cell with more than three live neighbours dies, as if by overpopulation.
      // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
      if (is_alive)
      {
        if (n < 2)
        {
          world.SetNext(i, j, {(uint8_t)DEAD});
        }
        else if ((n == 2) || (n == 3))
        {
          world.SetNext(i, j, {(uint8_t)ALIVE});
        }
        else if (n > 3)
        {
          world.SetNext(i, j, {(uint8_t)DEAD});
        }
      }
      else
      {
        if (n == 3)
        {
          world.SetNext(i, j, {(uint8_t)ALIVE});
        }
      }
#endif
    }
  }
  /* always last */
  world.SwapBuffers();
}

int JohnConway::CountNeighbors(const World &world, int x, int y) const
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
