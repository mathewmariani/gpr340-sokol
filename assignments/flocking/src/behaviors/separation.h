#pragma once

#include "flockingbehavior.h"

class Separation : public FlockingBehavior
{
public:
  explicit Separation(float weight = 4.75f, bool enabled = true)
      : FlockingBehavior(weight, enabled) {}

  const std::string GetName() const override { return "Separation"; }
  Vector2f ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &boid) const override;
};