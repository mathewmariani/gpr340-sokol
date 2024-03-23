/* engine */
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "math/math.h"
#include "mouse/mouse.h"
#include "imgui/imgui.h"

/* batteries */
#include "batteries/agent.h"
#include "batteries/colors.h"

namespace
{
  constexpr engine::graphics::DrawMode line = engine::graphics::DrawMode::DRAW_MODE_LINE;
  constexpr engine::graphics::DrawMode fill = engine::graphics::DrawMode::DRAW_MODE_FILL;
}

struct
{
  /* FIXME: clean this up; its very messy. */
  float radius = 45.0f;
  float mouse_strength = 0.5f;
  float wind_strength = 1.0f;
  float bbox_strength = 1.0f;

  bool show_acceleration = true;
  bool show_mouse_force = true;
  bool show_wind_force = true;
  bool show_bbox = true;

  float wind_direction = 0.0f;

  bool use_mouse_influence = true;
  bool use_wind_influence = true;
  bool use_bbox_influence = true;

  float turn_factor = 1.0f;

  float margin = 100.f;

  bool show_wind = true;

} debug;

/* implementation */
class Boid : public Agent
{
private:
  Vector2f mouse_influence(void)
  {
    if (!debug.use_mouse_influence)
    {
      return Vector2f::zero;
    }
    Vector2f mouse{engine::mouse::get_x(), engine::mouse::get_y()};
    return (mouse - position).normalized();
  }

  Vector2f wind_influence(void)
  {
    if (!debug.use_wind_influence)
    {
      return Vector2f::zero;
    }
    Vector2f wind{std::cosf(debug.wind_direction), std::sinf(debug.wind_direction)};
    return (velocity - wind).normalized();
  }

  Vector2f bbox_influence(void)
  {
    if (!debug.use_bbox_influence)
    {
      return Vector2f::zero;
    }

    int width, height;
    engine::graphics::get_dimensions(&width, &height);

    auto force = Vector2f::zero;
    if (position.x < debug.margin)
    {
      force += Vector2f::right * debug.turn_factor;
    }
    else if (position.x > (width - debug.margin))
    {
      force += Vector2f::left * debug.turn_factor;
    }
    if (position.y > (height - debug.margin))
    {
      force += Vector2f::down * debug.turn_factor;
    }
    else if (position.y < debug.margin)
    {
      force += Vector2f::up * debug.turn_factor;
    }
    return force;
  }

public:
  Boid() : Agent()
  {
    r = engine::math::random(0.0f, 1.0f);
    g = engine::math::random(0.0f, 1.0f);
    b = engine::math::random(0.0f, 1.0f);
  }

  void update(float dt)
  {
    cache.mouse_force = mouse_influence();
    cache.wind_force = wind_influence();
    cache.bbox_force = bbox_influence();

    /* apply all forces */
    apply_force(cache.mouse_force * debug.mouse_strength);
    apply_force(cache.wind_force * debug.wind_strength);
    apply_force(cache.bbox_force * debug.bbox_strength);

    /* physics step */
    physics_update(dt);

    /* cache */
    cache.acceleration = acceleration.normalized();
  }

  void draw(void)
  {
    /* FIXME: should be cached somewhere */
    constexpr auto l = 40.0f;
    constexpr auto w = 20.0f;
    Vector2f coords[]{{-l / 2, -w / 2}, {-l / 2, w / 2}, {l / 2, 0}, {-l / 2, -w / 2}};

    if (debug.show_acceleration)
    {
      auto x0 = position.x;
      auto y0 = position.y;
      auto x1 = x0 + cache.acceleration.x * debug.radius;
      auto y1 = y0 + cache.acceleration.y * debug.radius;
      engine::graphics::set_color(colors::Honeydew);
      engine::graphics::line(x0, y0, x1, y1);
    }

    if (debug.show_mouse_force)
    {
      auto x0 = position.x;
      auto y0 = position.y;
      auto x1 = x0 + cache.mouse_force.x * debug.radius;
      auto y1 = y0 + cache.mouse_force.y * debug.radius;
      engine::graphics::set_color(colors::Crimson);
      engine::graphics::line(x0, y0, x1, y1);
    }

    if (debug.show_wind_force)
    {
      auto x0 = position.x;
      auto y0 = position.y;
      auto x1 = x0 + cache.wind_force.x * debug.radius;
      auto y1 = y0 + cache.wind_force.y * debug.radius;
      // auto x1 = x0 + std::cosf(debug.wind_direction) * debug.radius;
      // auto y1 = y0 + std::sinf(debug.wind_direction) * debug.radius;

      engine::graphics::set_color(colors::CornflowerBlue);
      engine::graphics::line(x0, y0, x1, y1);
    }

    float forward_angle = std::atan2(forward.y, forward.x);

    engine::graphics::set_color(r, g, b, 1.0f);
    engine::graphics::push_transform();
    engine::graphics::translate(position.x, position.y);
    engine::graphics::rotate(forward_angle);
    engine::graphics::polyline(coords, 4);
    engine::graphics::pop_transform();
  }

private:
  float r, g, b;
  struct
  {
    Vector2f acceleration;
    Vector2f mouse_force;
    Vector2f wind_force;
    Vector2f bbox_force;
  } cache;
};

#define STUBBED() \
  std::printf("[%s]\n", __FUNCTION__)

static void load(void);
static void cleanup(void);
static void update(float);
static void draw(void);
static void gui(void);

game_desc game_main(int argv, char *argc[])
{
  game_desc desc{
      /* callbacks */
      .load_cb = load,
      .cleanup_cb = cleanup,
      .update_cb = update,
      .draw_cb = draw,
      .gui_cb = gui,

      /* config */
      .config = {
          .window = {
              .title = "Behavioral Agent",
              .width = 800,
              .height = 800,
          },
      },
  };
  return desc;
}

Boid *_boid;

static void load(void)
{
  _boid = new Boid();
}

static void cleanup(void)
{
  if (_boid)
  {
    delete _boid;
    _boid = nullptr;
  }
}

static void update(float dt)
{
  if (_boid)
  {
    _boid->update(dt);
  }
}

static void draw(void)
{
  if (debug.show_bbox)
  {
    int width, height;
    engine::graphics::get_dimensions(&width, &height);

    auto mx = width - (debug.margin * 2);
    auto my = height - (debug.margin * 2);
    engine::graphics::set_color(colors::WhiteSmoke);
    engine::graphics::rectangle(line, debug.margin, debug.margin, mx, my);
  }
  if (_boid)
  {
    _boid->draw();
  }
}

static void gui()
{
  if (ImGui::BeginMainMenuBar())
  {
    ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS", ImGui::GetIO().DeltaTime * 1000, 1.0f / ImGui::GetIO().DeltaTime, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::EndMainMenuBar();
  }

  ImGui::Begin("Settings", nullptr);

  if (ImGui::CollapsingHeader("Boid"))
  {
    auto pos = _boid->get_position();
    ImGui::Text("position (%.2f, %.2f)", pos.x, pos.y);

    /* debug drawing */
    ImGui::Checkbox("Show Mouse Force", &debug.show_mouse_force);
    ImGui::Checkbox("Show Wind Force", &debug.show_wind_force);
  }

  ImGui::DragFloat("Margin", &debug.margin, 0.1f, 0.0f, 350.0f);

  /* bbox */
  if (ImGui::CollapsingHeader("Bounding Box"))
  {
    ImGui::Checkbox("Use Bounding Box Influence", &debug.use_bbox_influence);
    ImGui::DragFloat("Bounding Box Strength", &debug.bbox_strength, 0.1f, 0.0f, 10.0f);
  }

  /* mouse */
  if (ImGui::CollapsingHeader("Mouse"))
  {
    ImGui::Checkbox("Use Mouse Influence", &debug.use_mouse_influence);
    ImGui::DragFloat("Mouse Strength", &debug.mouse_strength, 0.1f, 0.0f, 10.0f);
  }

  /* wind */
  if (ImGui::CollapsingHeader("Wind"))
  {
    ImGui::Checkbox("Use Wind Influence", &debug.use_wind_influence);
    ImGui::Checkbox("Show Wind", &debug.show_wind);
    ImGui::DragFloat("Wind Strength", &debug.wind_strength, 0.1f, 0.0f, 100.0f);
    ImGui::DragFloat("Wind Direction", &debug.wind_direction, 0.1f, 0.0f, 2 * ENGINE_PI);
  }

  ImGui::End();
}