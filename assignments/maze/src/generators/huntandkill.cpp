#include "huntandkill.h"

bool HuntAndKill::Step(World &world)
{
  if (!initialized)
  {
    initialized = true;
    auto point = RandomStartPoint(world);

    /* add to frontier */
    frontier.push(point);
    world.SetNodeType(point, NodeType::Frontier);
    return true;
  }

  if (frontier.empty())
  {
    std::vector<batteries::grid_location<int>> visitables;
    batteries::grid_location<int> parent{0, 0};
    batteries::grid_location<int> next{0, 0};

    for (auto j = 0; j < world.Width(); ++j)
    {
      for (auto i = 0; i < world.Width(); ++i)
      {
        parent = {i, j};
        if (world.GetNodeType(parent) == NodeType::Visited)
        {
          visitables = getVisitables(world, parent);
          if (visitables.empty())
          {
            continue;
          }

          auto k = engine::math::random(0, visitables.size() - 1);
          auto next = visitables[k];

          CreatePathBetween(world, parent, next);

          /* add to frontier */
          frontier.push(next);
          world.SetNodeType(next, NodeType::Frontier);
          return true;
        }
      }
    }
  }
  else
  {
    /* pick a random point from frontier */
    auto parent = frontier.front();

    /* remove point from frontier */
    world.SetNodeType(parent, NodeType::Visited);
    frontier.pop();

    auto visitables = getVisitables(world, parent);
    if (!visitables.empty())
    {
      auto i = engine::math::random(0, visitables.size() - 1);
      auto next = visitables[i];

      CreatePathBetween(world, parent, next);

      /* add to frontier */
      frontier.push(next);
      world.SetNodeType(next, NodeType::Frontier);
    }
    return true;
  }

  return false;
}

void HuntAndKill::Clear(World &world)
{
  initialized = false;
  while (!frontier.empty())
  {
    frontier.pop();
  }
}

std::vector<batteries::grid_location<int>> HuntAndKill::getVisitables(World &world, const batteries::grid_location<int> &point)
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

std::vector<batteries::grid_location<int>> HuntAndKill::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
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