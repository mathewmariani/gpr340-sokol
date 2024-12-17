#pragma once

#include "../world.h"

#include <string>

class Search
{
public:
  Search() = default;
  virtual ~Search() = default;

  virtual std::string GetName() = 0;

  virtual std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> Find(World &world, const batteries::grid_location<int> &start) = 0;

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
  inline bool IsPositionInBounds(const World &world, const batteries::grid_location<int> &tile) const
  {
    return (tile.x >= 0) && (tile.x < world.Width()) && (tile.y >= 0) && (tile.y < world.Width());
  }
};