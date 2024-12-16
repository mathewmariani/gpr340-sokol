#pragma once

// batteries
#include "batteries/finitegrid.h"

#include <string>

class Object
{
public:
  Object() = default;
  virtual ~Object() = default;

  virtual std::string GetName() = 0;

  inline batteries::Tile<int> GetGridLocation()
  {
    return grid_location;
  }

protected:
  batteries::Tile<int> grid_location;
};