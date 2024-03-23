#pragma once

#include <vector>
#include <unordered_map>

#include "grid_location.h"

namespace batteries
{
  template <class T>
  class finite_grid
  {
  public:
    finite_grid() : width(0) {}
    finite_grid(int width_) : width(width_) {}

  public:
    auto begin() const { return map.begin(); }
    auto end() const { return map.end(); }
    const auto cbegin() const { return map.begin(); }
    const auto cend() const { return map.end(); }

    auto contains(const grid_location<int> &tile) const { return map.contains(tile); }

    auto &at(const grid_location<int> &tile) { return map.at(tile); }
    const auto &at(const grid_location<int> &tile) const { return map.at(tile); }

    const auto size() const { return map.size(); }

    void clear()
    {
      map.clear();
    }
    void resize(int new_width)
    {
      width = new_width;

      map.clear();
      map.reserve(new_width * new_width);

      for (auto y = 0; y < new_width; ++y)
      {
        for (auto x = 0; x < new_width; ++x)
        {
          map[{x, y}] = T();
        }
      }
    }

    auto neighbors(const grid_location<int> &tile) const
    {
      std::vector<grid_location<int>> ret;
      for (const auto &dt : grid_location<int>::MooresNeighborhood)
      {
        auto n = tile + dt;
      }
      return ret;
    }

  public:
    static grid_location<float> pixel_to_tile(float size, int x, int y);
    static grid_location<int> tile_round(grid_location<float> t);

  private:
    std::size_t width;
    std::unordered_map<grid_location<int>, T> map;
  };

  template <class T>
  grid_location<float> finite_grid<T>::pixel_to_tile(float size, int x, int y)
  {
    auto px = (x / size);
    auto py = (y / size);
    return {(x / size), (y / size)};
  }

  template <class T>
  grid_location<int> finite_grid<T>::tile_round(grid_location<float> t)
  {
    return {(int)std::floor(t.x), (int)std::floor(t.y)};
  }
}