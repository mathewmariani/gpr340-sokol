#include "boundingbox.h"

Vector2f BoundingBox::ComputeForce(const std::vector<Boid *> &neighborhood, const Boid &agent) const
{
  // if (!debug.use_bbox_influence)
  // {
  //   return Vector2f::zero;
  // }

  // int width, height;
  // engine::graphics::get_dimensions(&width, &height);

  // auto force = Vector2f::zero;
  // if (position.x < debug.margin)
  // {
  //   force += Vector2f::right * debug.turn_factor;
  // }
  // else if (position.x > (width - debug.margin))
  // {
  //   force += Vector2f::left * debug.turn_factor;
  // }
  // if (position.y > (height - debug.margin))
  // {
  //   force += Vector2f::down * debug.turn_factor;
  // }
  // else if (position.y < debug.margin)
  // {
  //   force += Vector2f::up * debug.turn_factor;
  // }
  // return force;
  return Vector2f::zero;
}