#pragma once

/* batteies */
#include "batteries/hexgrid.h"

#include "agent.h"
#include "../world.h"

class Cat : public Agent
{
public:
  explicit Cat() = default;
  batteries::hexgrid_location<int> Move(World &world) override;
};