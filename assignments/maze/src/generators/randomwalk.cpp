#include "randomwalk.h"

bool RandomWalk::Step(World &world)
{
  if (!initialized)
  {
    initialized = true;
    auto point = RandomStartPoint(world);

    /* add to frontier */
    frontier.push_back(point);
    world.SetNodeType(point, NodeType::Frontier);
    return true;
  }

  /* pick a random point from frontier */
  auto i = engine::math::random(0, frontier.size() - 1);
  auto next = frontier[i];

  /* remove point from frontier */
  world.SetNodeType(next, NodeType::Visited);
  frontier.erase(frontier.begin() + i);

  auto visitables = getVisitables(world, next);
  for (auto node : visitables)
  {
    /* add to frontier */
    frontier.push_back(node);
    world.SetNodeType(node, NodeType::Frontier);
  }

  /* get all visited neighbors of next */
  auto neighbors = getVisitedNeighbors(world, next);
  if (!neighbors.empty())
  {
    /* pick a random visited neighbor */
    auto j = engine::math::random(0, neighbors.size() - 1);
    auto parent = neighbors[j];

    CreatePathBetween(world, parent, next);
  }

  if (frontier.size() == 0)
  {
    return false;
  }

  return true;
}

void RandomWalk::Clear(World &world)
{
  frontier.clear();
  initialized = false;
}

std::vector<batteries::grid_location<int>> RandomWalk::getVisitables(World &world, const batteries::grid_location<int> &point)
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

std::vector<batteries::grid_location<int>> RandomWalk::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
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