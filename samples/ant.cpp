/* engine */
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "math/math.h"
#include "mouse/mouse.h"
#include "imgui/imgui.h"

constexpr engine::graphics::DrawMode line = engine::graphics::DrawMode::DRAW_MODE_LINE;
constexpr engine::graphics::DrawMode fill = engine::graphics::DrawMode::DRAW_MODE_FILL;

class Ant;
class Pheromone;

struct
{
  struct
  {
    /* debug */
    bool show_acceleration = true;
    bool show_sensors = true;

    /* pheromone */
    float pheromone_size = 5.0f;

    /* ant */
    float ant_sensor_spread = 0.785398f;
    float ant_sensor_radius = 80.0f;
    float ant_pheromone_timer = 0.25f;

    float ant_steer_strength = 0.00f;
    float ant_mouse_strength = 5.00f;
    float ant_wander_strength = 0.04f;
    float ant_pheromone_strength = 1.25f;
  } debug;

  struct
  {
    std::vector<Pheromone> pheromones;
    std::vector<Ant> ants;
  } world;
} state;

#define STUBBED() \
  std::printf("[%s]\n", __FUNCTION__)

static void load(void);
static void cleanup(void);
static void update(float);
static void draw(void);
static void gui(void);
static void mouse_pressed(float, float, int);

Vector2f random_in_circle()
{
  return {engine::math::random(-1.0f, +1.0f), engine::math::random(-1.0f, +1.0f)};
}

class Pheromone
{
private:
  float strength = 5.0f;
  float max_strength = 5.0f;

private:
  Vector2f position;

public:
  Pheromone(const Vector2f &position_) : position(position_) {}

public:
  inline float get_strength(void) const
  {
    auto r = strength / max_strength;
    return (r > 0.0f) ? r : 0.0f;
  }

  inline Vector2f get_position(void) const
  {
    return position;
  }

public:
  void update(float dt)
  {
    strength -= dt;
  }

  void draw() const
  {
    engine::graphics::set_color(1.0f, 0.0f, 0.0f, get_strength());
    engine::graphics::circle(line, position.x, position.y, state.debug.pheromone_size);
  }
};

class Sensor
{
  friend class Ant;

private:
  float radius = 30.0f;
  float strength = 0.0f;
  bool intersection;

private:
  Vector2f position{0, 0};

public:
  float get_strength(void)
  {
    return strength;
  }

public:
  void update(float dt)
  {
    /* reset state */
    intersection = false;
    strength = 0.0f;

    for (const auto &p : state.world.pheromones)
    {
      float dx = position.x - p.get_position().x;
      float dy = position.y - p.get_position().y;
      float r = radius + state.debug.pheromone_size;
      if ((dx * dx + dy * dy) <= (r * r))
      {
        intersection = true;
        strength += p.get_strength();
      }
    }
  }

  void draw() const
  {
    if (intersection)
    {
      engine::graphics::set_color(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
      engine::graphics::set_color(1.0f, 1.0f, 0.0f, 1.0f);
    }

    engine::graphics::circle(line, position.x, position.y, radius);
  }
};

class Ant
{
private:
  float max_speed = 120.0f;
  float max_acceleration = 10.0f;
  float pheromone_timer = 1.0f;

private:
  Vector2f position{400, 400};
  Vector2f velocity{0, 0};
  Vector2f acceleration{0, 0};
  Vector2f desired{0, 0};
  Vector2f prev_acc{0, 0};

  float forward = 0.0f;

  Sensor sensors[3];

private:
  Vector2f mouse_influence(void)
  {
    Vector2f mouse{engine::mouse::get_x(), engine::mouse::get_y()};
    return (mouse - position).normalized();
  }

  Vector2f random_steering_force(void)
  {
    desired = (desired + random_in_circle() * state.debug.ant_wander_strength).normalized();
    auto desired_velocity = desired * max_speed;
    return (desired_velocity - velocity).normalized();
  }

  Vector2f pheromone_steering(void)
  {
    auto direction = Vector2f::zero;

    auto left = sensors[0].get_strength();
    auto center = sensors[1].get_strength();
    auto right = sensors[2].get_strength();
    auto a = 0.0f;

    if (center > std::max(left, right))
    {
      a = forward + (state.debug.ant_sensor_spread * 0);
      direction = {std::cos(a), std::sin(a)};
    }
    else if (left > right)
    {
      a = forward + (state.debug.ant_sensor_spread * -1);
      direction = {std::cos(a), std::sin(a)};
    }
    else if (right > left)
    {
      a = forward + (state.debug.ant_sensor_spread * +1);
      direction = {std::cos(a), std::sin(a)};
    }

    return direction;
  }

public:
  Ant(float forward_) : forward(forward_) {}

  void update(float dt)
  {
    /* pheromone step */
    pheromone_timer -= dt;
    if (pheromone_timer < 0.0f)
    {
      pheromone_timer = state.debug.ant_pheromone_timer;
      state.world.pheromones.push_back({position});
    }

    /* physics step */
    acceleration = Vector2f::zero;
    // acceleration += mouse_influence() * state.debug.ant_mouse_strength;
    acceleration += random_steering_force() * state.debug.ant_steer_strength;
    acceleration += pheromone_steering() * state.debug.ant_pheromone_strength;

    if (acceleration.magnitude() > max_acceleration)
    {
      acceleration = acceleration.normalized() * max_acceleration;
    }

    /* integration step */
    velocity = (velocity + acceleration).normalized() * max_speed;
    position = position + velocity * dt;

    /* screen wrap */
    if (position.x > 800.0f)
    {
      position.x = 0.0f;
    }
    else if (position.x < 0.0f)
    {
      position.x = 800.0f;
    }
    if (position.y > 800.0f)
    {
      position.y = 0.0f;
    }
    else if (position.y < 0.0f)
    {
      position.y = 800.0f;
    }

    /* cache */
    forward = std::atan2(velocity.y, velocity.x);
    prev_acc = acceleration.normalized();

    /* update sensors */
    auto a = 0.0f;
    for (auto i = -1, j = 0; i <= 1; ++i, ++j)
    {
      a = forward + (state.debug.ant_sensor_spread * i);
      sensors[j].position.x = position.x + state.debug.ant_sensor_radius * std::cos(a);
      sensors[j].position.y = position.y + state.debug.ant_sensor_radius * std::sin(a);
      sensors[j].update(dt);
    }
  }

  void draw(void)
  {
    constexpr auto l = 40.0f;
    constexpr auto w = 20.0f;
    Vector2f coords[]{{-l / 2, -w / 2}, {-l / 2, w / 2}, {l / 2, 0}};

    auto x0 = position.x;
    auto y0 = position.y;

    if (state.debug.show_acceleration)
    {
      auto x1 = x0 + prev_acc.x * state.debug.ant_sensor_radius;
      auto y1 = y0 + prev_acc.y * state.debug.ant_sensor_radius;
      engine::graphics::set_color(1.0f, 0.0f, 0.0f, 1.0f);
      engine::graphics::line(x0, y0, x1, y1);
    }

    engine::graphics::set_color(1.0f, 1.0f, 0.0f, 1.0f);
    engine::graphics::push_transform();
    engine::graphics::translate(x0, y0);
    engine::graphics::rotate(forward);
    engine::graphics::polygon(fill, coords, 3);
    engine::graphics::pop_transform();

    if (state.debug.show_sensors)
    {
      for (auto i = 0; i < 3; ++i)
      {
        sensors[i].draw();
      }
    }
  }
};

game_desc game_main(int argv, char *argc[])
{
  game_desc desc{
      .load_cb = load,
      .cleanup_cb = cleanup,
      .update_cb = update,
      .draw_cb = draw,
      .gui_cb = gui,
      .mouse_pressed_cb = mouse_pressed,
  };
  return desc;
}
static void load(void)
{
  for (auto i = 0; i < 50; ++i)
  {

    state.world.ants.push_back({engine::math::random(0.0f, 360.0f)});
  }
}
static void cleanup(void)
{
  STUBBED();
}
static void update(float dt)
{
  for (auto &a : state.world.ants)
  {
    a.update(dt);
  }

  auto itr = state.world.pheromones.begin();
  while (itr != state.world.pheromones.end())
  {
    if ((*itr).get_strength() <= 0.0f)
    {
      itr = state.world.pheromones.erase(itr);
    }
    (*itr).update(dt);
    ++itr;
  }
}

static void draw(void)
{
  for (auto &a : state.world.ants)
  {
    a.draw();
  }

  for (auto &p : state.world.pheromones)
  {
    p.draw();
  }
}
static void gui()
{
  ImGui::Begin("Settings", nullptr);

  // ImGui::Text("Velocity (%.2f, %.2f)", velocity.x, velocity.y);

  ImGui::Text("Steer Strength");
  ImGui::DragFloat("##drag_steer_strength", &state.debug.ant_steer_strength, 0.01f, 0.0f, 6.0f);

  ImGui::Text("Mouse Strength");
  ImGui::DragFloat("##drag_mouse_strength", &state.debug.ant_mouse_strength, 0.01f, 0.0f, 6.0f);

  ImGui::Text("Wander Strength");
  ImGui::DragFloat("##drag_wander_strength", &state.debug.ant_wander_strength, 0.01f, 0.0f, 360.0f);

  ImGui::Text("Pheromone Strength");
  ImGui::DragFloat("##drag_pheromone_strength", &state.debug.ant_pheromone_strength, 0.01f, 0.0f, 360.0f);

  ImGui::Text("Show Acceleration");
  ImGui::Checkbox("##checbox_show_acceleration", &state.debug.show_acceleration);

  ImGui::Text("Spread");
  ImGui::DragFloat("##drag_ant_sensor_spread", &state.debug.ant_sensor_spread, 0.01f, 0.0f, 2 * ENGINE_PI);

  ImGui::Text("Radius");
  ImGui::DragFloat("##drag_ant_sensor_radius", &state.debug.ant_sensor_radius, 1.0f, 0.0f, 255.0f);

  ImGui::Text("Pheromone Timer");
  ImGui::DragFloat("##drag_ant_pheromone_timer", &state.debug.ant_pheromone_timer, 0.25f, 0.0f, 255.0f);

  ImGui::End();
}

static void mouse_pressed(float x, float y, int button)
{
  state.world.pheromones.push_back({{x, y}});
}