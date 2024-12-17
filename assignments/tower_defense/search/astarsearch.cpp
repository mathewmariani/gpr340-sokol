// engine
#include "graphics/graphics.h"

#include "astarsearch.h"
#include "../heuristic/heuristic.h"

std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> AStarSearch::Find(World &world, const batteries::grid_location<int> &start)
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

std::vector<batteries::grid_location<int>> AStarSearch::getVisitables(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> visitables;
  batteries::grid_location<int> next{0, 0};

  for (const auto &delta : batteries::grid_location<int>::VonNewmanNeighborhood)
  {
    next = point + delta;
    if (IsPositionInBounds(world, next) && (world.GetNodeType(next) != NodeType::Wall))
    {
      visitables.emplace_back(next);
    }
  }

  return visitables;
}

std::vector<batteries::grid_location<int>> AStarSearch::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> neighbors;
  return neighbors;
}