#include "separation.h"

#include "../agents/boid.h"

Vector2f Separation::ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &agent) const
{
  constexpr float desiredMinimalDistance = 24.0f;
  if (neighborhood.empty())
  {
    return Vector2f::zero;
  }

  int count = 0;
  float distance = 0.0f;
  Vector2f average_position{0, 0};
  for (const auto *neighbor : neighborhood)
  {
    distance = Vector2f::distance(agent.get_position(), neighbor->get_position());
    if (distance < desiredMinimalDistance)
    {
      average_position += neighbor->get_position();
      count++;
    }
  }

  if (count == 0)
  {
    return Vector2f::zero;
  }

  average_position /= count;

  auto separation_force = agent.get_position() - average_position;
  return separation_force.normalized();
}