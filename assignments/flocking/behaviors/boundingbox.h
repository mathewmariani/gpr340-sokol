#pragma once

#include "flockingbehavior.h"

class BoundingBox : public FlockingBehavior
{
public:
  explicit BoundingBox(float weight = 2.90f, bool enabled = true)
      : FlockingBehavior(weight, enabled) {}

  const std::string GetName() const override { return "BoundingBox"; }
  Vector2f ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &agent) const override;
};