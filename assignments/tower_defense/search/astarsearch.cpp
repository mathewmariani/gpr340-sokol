#include "../pathfinding.h"
#include "../heuristic/heuristic.h"

// batteries
#include "batteries/grid_location.h"

#include <queue>
#include <vector>

struct GridNode
{
  int cost;
  batteries::grid_location<int> location;

  bool operator<(const GridNode &other) const
  {
    return cost < other.cost;
  }
};

std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> Pathfinding::AStarSearch(const World &world, const batteries::grid_location<int> &start)
{
  std::priority_queue<GridNode> frontier;
  frontier.push((GridNode){.cost = 0, .location = start});

  std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> came_from;
  came_from.insert({start, start});

  while (!frontier.empty())
  {
    /* check for visitable neighbors */
    auto current = frontier.top().location;
    auto visitables = getVisitables(world, current);

    int priority = 0;
    for (const auto &next : visitables)
    {
      if (!came_from.contains(next))
      {
        // priority = ManhattanDistance(goal, next)
        frontier.push((GridNode){.cost = priority, .location = next});
        came_from.insert({next, current});
      };
    }

    frontier.pop();
  }

  return came_from;
}