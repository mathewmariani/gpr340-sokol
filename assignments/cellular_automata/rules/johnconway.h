#pragma once

#include "rulebase.h"

class JohnConway : public RuleBase
{
public:
  explicit JohnConway() = default;
  ~JohnConway() override = default;

  const std::string GetName() override { return "John Conway"; }

  void Step(World &world) override;
  int CountNeighbors(const World &world, int x, int y) const override;
};