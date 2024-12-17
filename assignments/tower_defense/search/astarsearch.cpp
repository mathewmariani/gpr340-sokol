// engine
#include "graphics/graphics.h"

#include "astarsearch.h"
#include "../heuristic/heuristic.h"

void AStarSearch::Clear(World &world)
{
  while (!frontier.empty())
  {
    frontier.pop();
  }
  reached.clear();
}

void AStarSearch::Find(World &world, const batteries::grid_location<int> &start)
{
  frontier.push((GridNode){.cost = 0, .location = start});
  reached.insert({start, true});

  while (!frontier.empty())
  {
    /* check for visitable neighbors */
    auto current = frontier.top().location;
    auto visitables = getVisitables(world, current);

    int priority = 0;
    for (const auto &next : visitables)
    {
      if (!reached.contains(next))
      {
        // priority = ManhattanDistance(goal, next)
        frontier.push((GridNode){.cost = priority, .location = next});
        reached.insert({next, true});
      };
    }

    frontier.pop();
  }
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