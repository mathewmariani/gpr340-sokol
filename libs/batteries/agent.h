#pragma once

#include "common/vector2.h"

namespace batteries
{
  class Agent
  {
  protected:
    Vector2f position{0, 0};
    Vector2f velocity{0, 0};
    Vector2f acceleration{0, 0};
    Vector2f forward{0, 0};

    float max_speed = 120.0f;
    float max_acceleration = 10.0f;

  public:
    Agent() : position({40, 40}), velocity({0, 0}), acceleration({0, 0}), forward({0, 0}){};

  public:
    const Vector2f &get_position(void) const
    {
      return position;
    }
    void set_position(const Vector2f &position)
    {
      this->position = position;
    }

    const Vector2f &get_velocity(void) const
    {
      return velocity;
    }
    void set_velocity(const Vector2f &velocity)
    {
      this->velocity = velocity;
    }

    const Vector2f &get_acceleration(void) const
    {
      return acceleration;
    }
    void set_acceleration(const Vector2f &acceleration)
    {
      this->acceleration = acceleration;
    }

  public:
    void apply_force(const Vector2f &force)
    {
      acceleration += force;
    }

    void physics_update(float dt)
    {
      if (acceleration.magnitude() > max_acceleration)
      {
        acceleration = acceleration.normalized() * max_acceleration;
      }

      /* integration step */
      velocity = (velocity + acceleration).normalized() * max_speed;
      position = position + velocity * dt;

      /* cache */
      forward = velocity.normalized();
    }
  };
}