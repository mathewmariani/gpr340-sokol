#pragma once

#include "../world.h"
#include <string>

class RuleBase
{
public:
  virtual ~RuleBase() = default;
  virtual const std::string GetName() = 0;

  virtual void Step(World &world) = 0;
  virtual int CountNeighbors(const World &world, int x, int y) const = 0;
};