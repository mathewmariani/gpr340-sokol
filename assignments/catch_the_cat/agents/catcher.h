#pragma once

/* batteies */
#include "batteries/hexgrid.h"

#include "agent.h"
#include "../world.h"

class Catcher : public Agent
{
public:
  explicit Catcher() = default;
  batteries::hexgrid_location<int> Move(World &world) override;
};