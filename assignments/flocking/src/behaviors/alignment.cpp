#include "alignment.h"

#include "../agents/boid.h"

Vector2f Alignment::ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &agent) const
{
  Vector2f average_velocity{0, 0};
  for (const auto &other : neighborhood)
  {
    average_velocity += other->get_velocity();
  }
  // average_velocity /= neighborhood.size();

  auto alignment_force = average_velocity - agent.get_velocity();
  return alignment_force.normalized();
}