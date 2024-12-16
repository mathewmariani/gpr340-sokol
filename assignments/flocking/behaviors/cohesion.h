#pragma once

#include "flockingbehavior.h"

class Cohesion : public FlockingBehavior
{
public:
    explicit Cohesion(float weight = 4.25f, bool enabled = true)
        : FlockingBehavior(weight, enabled) {}

    const std::string GetName() const override { return "Cohesion"; }
    Vector2f ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &agent) const override;
};