#pragma once

#include "batteries/agent.h"

class Boid : public batteries::Agent
{
public:
  static std::unique_ptr<Boid> Create();
  static std::vector<Boid *> GetNeighborhood(const Boid *boid);

public:
  Boid();
  ~Boid() = default;

  static std::vector<std::unique_ptr<Boid>> all;

  void Update(float dt);
  void Draw();

  const float get_radius() const { return radius; }

protected:
  float max_speed = 120.0f;
  float max_acceleration = 10.0f;
  float radius = 35.0f;

  float r, g, b;
};