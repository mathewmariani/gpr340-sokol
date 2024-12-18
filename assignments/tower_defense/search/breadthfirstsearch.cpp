#include "../pathfinding.h"
#include "../heuristic/heuristic.h"

// batteries
#include "batteries/grid_location.h"

#include <unordered_map>
#include <vector>

std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> Pathfinding::BreadthFirstSearch(const World &world, const batteries::grid_location<int> &start)
{
  std::vector<batteries::grid_location<int>> frontier;
  frontier.push_back(start);

  std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> came_from;
  came_from.insert({start, start});

  while (!frontier.empty())
  {
    auto current = frontier.front();
    for (const auto &next : getVisitables(world, current))
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