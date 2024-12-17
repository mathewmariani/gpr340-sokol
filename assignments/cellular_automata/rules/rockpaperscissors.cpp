#include "rockpaperscissors.h"

namespace
{
  enum
  {
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2,
  };
}

void RockPaperScissors::Step(World &world)
{
  /* always last */
  world.SwapBuffers();
}

int RockPaperScissors::CountNeighbors(const World &world, int x, int y) const
{
  return 0;
}