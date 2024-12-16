#pragma once

#include "flockingbehavior.h"

class Alignment : public FlockingBehavior
{
public:
  explicit Alignment(float weight = 2.90f, bool enabled = true)
      : FlockingBehavior(weight, enabled) {}

  const std::string GetName() const override { return "Alignment"; }
  Vector2f ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &agent) const override;
};