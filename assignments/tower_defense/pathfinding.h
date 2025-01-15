#pragma once

#include "batteries/grid_location.h"
#include "batteries/grid_world.h"

namespace Pathfinding
{
  extern std::pair<std::vector<batteries::grid_location<int>>, std::map<batteries::grid_location<int>, batteries::grid_location<int>>> BreadthFirstSearch(const batteries::grid_world &grid, const batteries::grid_location<int> &start, int step_limit);
}