#include "cohesion.h"

#include "../agents/boid.h"

Vector2f Cohesion::ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &agent) const
{
  Vector2f average_position{0, 0};
  for (const auto &other : neighborhood)
  {
    average_position += other->get_position();
  }
  average_position /= neighborhood.size();

  auto cohesion_force = average_position - agent.get_position();
  return cohesion_force.normalized();
}