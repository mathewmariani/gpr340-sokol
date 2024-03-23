#pragma once

// engine
#include "math/math.h"

#include "../world.h"

#include <string>

class MazeGenerator
{
public:
  MazeGenerator() = default;
  virtual ~MazeGenerator() = default;

  virtual std::string GetName() = 0;

  virtual bool Step(World &world) = 0;
  virtual void Clear(World &world) = 0;

protected:
  inline batteries::grid_location<int> RandomStartPoint(const World &world) const
  {
    return {
        engine::math::random(0, world.Width()),
        engine::math::random(0, world.Width()),
    };
  }

  inline bool IsPositionInBounds(const World &world, const batteries::grid_location<int> &point) const
  {
    return (point.x >= 0) && (point.x < world.Width()) && (point.y >= 0) && (point.y < world.Width());
  }

  inline void CreatePathBetween(World &world, const batteries::grid_location<int> &parent, const batteries::grid_location<int> &next)
  {
    if (next == (parent + batteries::grid_location<int>::West))
    {
      world.SetEast(next, false);
    }
    else if (next == (parent + batteries::grid_location<int>::South))
    {
      world.SetSouth(next, false);
    }
    else if (next == (parent + batteries::grid_location<int>::East))
    {
      world.SetWest(next, false);
    }
    else if (next == (parent + batteries::grid_location<int>::North))
    {
      world.SetNorth(next, false);
    }
  }
};