#pragma once

#include "grid_location.h"

#include <map>
#include <vector>

namespace batteries
{
  class grid_world
  {
  public:
    grid_world() : width(0), height(0) {}
    grid_world(int width_, int height_) : width(width_), height(height_)
    {
      for (auto y = 0; y < height_; ++y)
      {
        for (auto x = 0; x < width_; ++x)
        {
          map[grid_location<int>{x, y}] = 0;
        }
      }
    }

  public:
    auto getWidth() const { return width; }
    auto getHeight() const { return height; }

    auto inRange(const grid_location<int> &location) const
    {
      return 0 <= location.x && location.x < width && 0 <= location.y && location.y < height;
    }

    auto isWall(const grid_location<int> &location) const
    {
      auto it = std::find(walls.begin(), walls.end(), location);
      return (it != walls.end());
    }

    auto toggleWall(const grid_location<int> &location)
    {
      auto it = std::find(walls.begin(), walls.end(), location);
      if (it != walls.end())
      {
        walls.erase(it);
      }
      else
      {
        walls.push_back(location);
      }
    }

    auto locations() const
    {
      return map;
    }

    auto neighbors(const grid_location<int> &location) const
    {
      auto neighbors = grid_location<int>::VonNewmanNeighborhood;
      if ((location.x + location.y) % 2 == 0)
      {
        std::reverse(neighbors.begin(), neighbors.end());
      }

      std::vector<grid_location<int>> ret;
      grid_location<int> next{0, 0};
      for (const auto &delta : neighbors)
      {
        next = location + delta;
        if (inRange(next) && !isWall(next))
        {
          ret.push_back(next);
        }
      }

      return ret;
    }

  private:
    int width;
    int height;
    std::map<grid_location<int>, int> map;
    std::vector<grid_location<int>> walls;
  };
}