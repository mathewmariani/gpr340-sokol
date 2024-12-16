#include "langtonsant.h"

namespace
{
  enum
  {
    BLACK = 0,
    WHITE = 1,
    ANT = 2,
  };
}

void LangtonsAnt::Step(World &world)
{
  /* always last */
  world.SwapBuffers();
}

int LangtonsAnt::CountNeighbors(const World &world, int x, int y) const
{
  return 0;
}