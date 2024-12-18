#pragma once

#include "world.h"

#include <algorithm>
#include <string>

class Pathfinding
{
public:
  Pathfinding() = delete;
  ~Pathfinding() = delete;

  static std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> AStarSearch(const World &world, const batteries::grid_location<int> &start);
  static std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> BreadthFirstSearch(const World &world, const batteries::grid_location<int> &start);
  static std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> DijkstraSearch(const World &world, const batteries::grid_location<int> &start);
  static std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> GreedySearch(const World &world, const batteries::grid_location<int> &start);

  static std::vector<batteries::grid_location<int>> ConstructPath(std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> came_from, const batteries::grid_location<int> &start, const batteries::grid_location<int> &goal)
  {
    std::vector<batteries::grid_location<int>> path{};
    if (!came_from.contains(goal))
    {
      return path;
    }
    auto current = goal;
    while (current != start)
    {
      path.emplace_back(current);
      current = came_from[current];
    }
    path.emplace_back(start);
    std::reverse(path.begin(), path.end());
    return path;
  }

protected:
  static inline bool IsPositionInBounds(const World &world, const batteries::grid_location<int> &tile)
  {
    return (tile.x >= 0) && (tile.x < world.Width()) && (tile.y >= 0) && (tile.y < world.Width());
  }

  static std::vector<batteries::grid_location<int>> getVisitables(const World &world, const batteries::grid_location<int> &point)
  {
    std::vector<batteries::grid_location<int>> visitables;
    auto neigbors = batteries::grid_location<int>::VonNewmanNeighborhood;
    if ((point.x + point.y) % 2 == 0)
    {
      std::reverse(neigbors.begin(), neigbors.end());
    }

    batteries::grid_location<int> next{0, 0};
    for (const auto &delta : neigbors)
    {
      next = point + delta;
      if (IsPositionInBounds(world, next) && (world.GetNodeType(next) != NodeType::Wall))
      {
        visitables.emplace_back(next);
      }
    }

    return visitables;
  }
};