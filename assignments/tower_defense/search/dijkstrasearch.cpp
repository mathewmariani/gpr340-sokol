#include "../pathfinding.h"
#include "../heuristic/heuristic.h"

// batteries
#include "batteries/grid_location.h"

#include <unordered_map>
#include <vector>

std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> Pathfinding::DijkstraSearch(const World &world, const batteries::grid_location<int> &start)
{
  std::vector<batteries::grid_location<int>> frontier;
  frontier.push_back(start);

  std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> came_from;
  came_from.insert({start, start});

  while (!frontier.empty())
  {
    /* check for visitable neighbors */
    auto current = frontier.front();
    auto visitables = getVisitables(world, current);

    for (const auto &next : visitables)
    {
      if (!came_from.contains(next))
      {
        frontier.push_back(next);
        came_from.insert({next, current});
      };
    }

    frontier.erase(frontier.begin());
  }

  return came_from;
}