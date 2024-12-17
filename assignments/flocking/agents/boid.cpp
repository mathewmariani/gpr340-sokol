#include "graphics/graphics.h"
#include "math/math.h"
#include "boid.h"

std::vector<std::unique_ptr<Boid>> Boid::all;

std::vector<Boid *> Boid::GetNeighborhood(const Boid *boid)
{
  std::vector<Boid *> neighborhood;

  auto radius2 = boid->radius * boid->radius;
  auto position = boid->get_position();

  for (const auto &other : all)
  {
    if (boid != other.get())
    {
      auto dist2 = Vector2f::sqrDistance(position, other->get_position());
      if (dist2 <= radius2)
      {
        neighborhood.push_back(other.get());
      }
    }
  }

  return neighborhood;
}

std::unique_ptr<Boid> Boid::Create()
{
  int width, height;
  engine::graphics::get_dimensions(&width, &height);

  /* random position and velocity */
  const auto x = engine::math::random(0.0f, (float)width);
  const auto y = engine::math::random(0.0f, (float)height);
  const auto a = engine::math::random(0.0f, 360.0f);

  auto boid = std::make_unique<Boid>();
  boid->set_position({x, y});
  boid->set_velocity(Vector2f::up.rotate(a) * 5.0f);

  return boid;
}

#define SCREENWRAP(pos, w, h) \
  if (pos.x < 0)              \
    pos.x += w;               \
  else if (pos.x > w)         \
    pos.x -= w;               \
  if (pos.y < 0)              \
    pos.y += h;               \
  else if (pos.y > h)         \
    pos.y -= h;

Boid::Boid()
{
  r = engine::math::random(0.0f, 1.0f);
  g = engine::math::random(0.0f, 1.0f);
  b = engine::math::random(0.0f, 1.0f);
}

void Boid::Update(float dt)
{
  physics_update(dt);

  // cheap screenwarp
  int w, h;
  engine::graphics::get_dimensions(&w, &h);
  SCREENWRAP(position, w, h);
}

void Boid::Draw()
{
  // FIXME: cache polygon coordinates.
  // FIXME: shouldnt need to define this every frame
  constexpr auto l = 10.0f;
  constexpr auto w = 5.0f;
  Vector2f coords[]{{-l / 2, -w / 2}, {-l / 2, w / 2}, {l / 2, 0}, {-l / 2, -w / 2}};

  auto x = position.x;
  auto y = position.y;
  auto forward = velocity.normalized();

  engine::graphics::set_color(r, g, b, 1.0f);
  engine::graphics::push_transform();
  engine::graphics::translate(x, y);
  engine::graphics::rotate(std::atan2(forward.y, forward.x));
  engine::graphics::polyline(coords, 4);
  engine::graphics::pop_transform();
}