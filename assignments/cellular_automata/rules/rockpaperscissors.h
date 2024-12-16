#pragma once

#include "rulebase.h"

class RockPaperScissors : public RuleBase
{
public:
  explicit RockPaperScissors() = default;
  ~RockPaperScissors() override = default;

  const std::string GetName() override { return "Rock Paper Scissors"; }

  void Step(World &world) override;
  int CountNeighbors(const World &world, int x, int y) const override;
};