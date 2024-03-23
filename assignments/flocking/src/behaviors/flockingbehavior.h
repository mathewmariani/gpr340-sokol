#pragma once

#include <string>
#include "common/vector2.h"

#include "../agents/boid.h"

class FlockingBehavior
{
public:
  explicit FlockingBehavior(float _weight, bool _enabled = true)
      : weight(_weight), enabled(_enabled) {}
  virtual ~FlockingBehavior() = default;

  virtual const std::string GetName() const = 0;
  virtual Vector2f ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &boid) const = 0;

  inline Vector2f ComputeWeightedForce(const std::vector<Boid *> &neighborhood, const Boid &boid)
  {
    return (!neighborhood.empty() && enabled) ? ComputeForce(neighborhood, boid) * weight : Vector2f::zero;
  }

public:
  bool enabled;
  float weight;

protected:
  Vector2f force;
};
