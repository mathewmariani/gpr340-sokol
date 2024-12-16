#pragma once

#include "rulebase.h"

class LangtonsAnt : public RuleBase
{
public:
  explicit LangtonsAnt() = default;
  ~LangtonsAnt() override = default;

  const std::string GetName() override { return "Langtons Ant"; }

  void Step(World &world) override;
  int CountNeighbors(const World &world, int x, int y) const override;
};