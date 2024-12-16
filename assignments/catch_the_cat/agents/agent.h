#pragma once

/* batteies */
#include "batteries/hexgrid.h"

class World;

class Agent
{
public:
  explicit Agent() = default;
  ~Agent() = default;

  virtual Hex<int> Move(World &world) = 0;

  std::vector<Hex<int>> GeneratePath(const World &world);

  inline const Hex<int> GetPosition() const
  {
    return position;
  };

protected:
  Hex<int> position;
};