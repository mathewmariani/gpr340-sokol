#pragma once

#include "flockingbehavior.h"

class MouseInfluence : public FlockingBehavior
{
public:
  explicit MouseInfluence(float weight = 2.90f, bool enabled = true)
      : FlockingBehavior(weight, enabled) {}

  const std::string GetName() const override { return "Mouse Influence"; }
  Vector2f ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &agent) const override;
};