// engine
#include "common/color.h"
#include "graphics/graphics.h"

#include "dijkstrasearch.h"

void DijkstraSearch::Clear(World &world)
{
  frontier.clear();
  distance.clear();
}

void DijkstraSearch::Find(World &world, const batteries::grid_location<int> &start)
{
  frontier.push_back(start);
  distance.insert({start, 0});

  while (!frontier.empty())
  {
    /* check for visitable neighbors */
    auto current = frontier.front();
    auto visitables = getVisitables(world, current);

    for (const auto &next : visitables)
    {
      if (!distance.contains(next))
      {
        frontier.push_back(next);
        distance.insert({next, 1 + distance[current]});
      };
    }

    frontier.erase(frontier.begin());
  }
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