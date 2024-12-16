#include "recursivebacktracker.h"

bool RecursiveBacktracker::Step(World &world)
{
  if (!initialized)
  {
    initialized = true;
    auto start = RandomStartPoint(world);

    /* add to frontier */
    frontier.push(start);
    world.SetNodeType(start, NodeType::Frontier);
    return true;
  }

  if (frontier.empty())
  {
    return false;
  }

  /* check for visitable neighbors */
  auto current = frontier.top();
  auto visitables = getVisitables(world, current);

  if (visitables.empty())
  {
    frontier.pop();
    world.SetNodeType(current, NodeType::Visited);
    return true;
  }
  else
  {
    /* get randon visitable neighbor */
    auto i = engine::math::random(0, visitables.size() - 1);
    auto next = visitables[i];

    /* add to frontier */
    frontier.push(next);
    world.SetNodeType(next, NodeType::Frontier);

    CreatePathBetween(world, current, next);
    return true;
  }

  return false;
}

void RecursiveBacktracker::Clear(World &world)
{
  initialized = false;
  while (!frontier.empty())
  {
    frontier.pop();
  }
}

std::vector<batteries::grid_location<int>> RecursiveBacktracker::getVisitables(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> visitables;
  batteries::grid_location<int> next{0, 0};
  for (const auto &delta : batteries::grid_location<int>::VonNewmanNeighborhood)
  {
    next = point + delta;
    if (IsPositionInBounds(world, next) && (world.GetNodeType(next) == NodeType::Unvisited))
    {
      visitables.push_back(next);
    }
  }

  return visitables;
}

std::vector<batteries::grid_location<int>> RecursiveBacktracker::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> neighbors;
  batteries::grid_location<int> next{0, 0};
  for (const auto &delta : batteries::grid_location<int>::VonNewmanNeighborhood)
  {
    next = point + delta;
    if (IsPositionInBounds(world, next) && (world.GetNodeType(next) == NodeType::Visited))
    {
      neighbors.push_back(next);
    }
  }

  return neighbors;
}