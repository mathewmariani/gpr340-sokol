#pragma once

#include "../world.h"

#include <string>

class Search
{
public:
  Search() = default;
  virtual ~Search() = default;

  virtual std::string GetName() = 0;

  virtual void Clear(World &world) = 0;
  virtual void Find(World &world, const batteries::grid_location<int> &start) = 0;

protected:
  inline bool IsPositionInBounds(const World &world, const batteries::grid_location<int> &tile) const
  {
    return (tile.x >= 0) && (tile.x < world.Width()) && (tile.y >= 0) && (tile.y < world.Width());
  }
};