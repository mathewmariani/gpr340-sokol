#pragma once

#include "rulebase.h"

class CaveGeneration : public RuleBase
{
public:
  explicit CaveGeneration() = default;
  ~CaveGeneration() override = default;

  const std::string GetName() override { return "Cave Generation"; }

  void Step(World &world) override;
  int CountNeighbors(const World &world, int x, int y) const override;
};