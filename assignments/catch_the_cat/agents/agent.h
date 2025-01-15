#pragma once

/* batteies */
#include "batteries/hexgrid.h"

class World;

class Agent
{
public:
  explicit Agent() = default;
  ~Agent() = default;

  virtual batteries::hexgrid_location<int> Move(World &world) = 0;

  std::vector<batteries::hexgrid_location<int>> GeneratePath(const World &world);

  inline const batteries::hexgrid_location<int> GetPosition() const
  {
    return position;
  };

protected:
  batteries::hexgrid_location<int> position;
};