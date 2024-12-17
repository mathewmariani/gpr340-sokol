// engine
#include "common/color.h"
#include "graphics/graphics.h"

#include "greedysearch.h"

void GreedySearch::Clear(World &world)
{
  frontier.clear();
  reached.clear();
}

void GreedySearch::Find(World &world, const batteries::grid_location<int> &start)
{
  // add to frontier
  frontier.push_back(start);
  reached.insert({start, true});

  while (!frontier.empty())
  {
    /* check for visitable neighbors */
    auto current = frontier.front();
    auto visitables = getVisitables(world, current);

    for (const auto &next : visitables)
    {
      if (!reached.contains(next))
      {
        frontier.push_back(next);
        reached.insert({next, true});
      };
    }

    frontier.erase(frontier.begin());
  }
}

std::vector<batteries::grid_location<int>> GreedySearch::getVisitables(World &world, const batteries::grid_location<int> &point)
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

std::vector<batteries::grid_location<int>> GreedySearch::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> neighbors;
  return neighbors;
}