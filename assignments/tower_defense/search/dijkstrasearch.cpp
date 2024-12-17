// engine
#include "common/color.h"
#include "graphics/graphics.h"

#include "dijkstrasearch.h"

std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> DijkstraSearch::Find(World &world, const batteries::grid_location<int> &start)
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

std::vector<batteries::grid_location<int>> DijkstraSearch::getVisitables(World &world, const batteries::grid_location<int> &point)
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

std::vector<batteries::grid_location<int>> DijkstraSearch::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> neighbors;
  return neighbors;
}