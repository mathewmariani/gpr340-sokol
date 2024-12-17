/* engine */
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "math/math.h"
#include "imgui/imgui.h"

/* behaviors */
#include "behaviors/alignment.h"
#include "behaviors/cohesion.h"
#include "behaviors/mouseinfluence.h"
#include "behaviors/separation.h"
#include "behaviors/flockingbehavior.h"

/* agents */
#include "agents/boid.h"
#include "batteries/agent.h"

#include <vector>
#include <memory>

namespace
{
  constexpr engine::graphics::DrawMode line = engine::graphics::DrawMode::DRAW_MODE_LINE;
  constexpr engine::graphics::DrawMode fill = engine::graphics::DrawMode::DRAW_MODE_FILL;

  constexpr int number_of_boids = 300;
}

static struct
{
  struct
  {
    bool show_radius = false;
    bool show_rules = false;
    bool show_acceleration = false;
  } debug;

  struct
  {
    bool paused = false;
    float factor = 1.0f;
  } time;

  std::vector<std::unique_ptr<FlockingBehavior>> flocking_behaviors;
} state;

static void load(void)
{
  /* create flocking behaviors */
  state.flocking_behaviors.emplace_back(std::make_unique<Separation>());
  state.flocking_behaviors.emplace_back(std::make_unique<Cohesion>());
  state.flocking_behaviors.emplace_back(std::make_unique<Alignment>());

  /* create all boids */
  for (auto i = 0; i < number_of_boids; ++i)
  {
    Boid::all.push_back(Boid::Create());
  }
}

static void cleanup(void)
{
  Boid::all.clear();
}

static void update(float dt)
{
  if (state.time.paused || state.time.factor == 0.0f)
  {
    return;
  }

  Vector2f weighted_force;
  for (auto &boid : Boid::all)
  {
    boid->Update(dt * state.time.factor);

    auto neighbors = Boid::GetNeighborhood(boid.get());
    for (auto &rule : state.flocking_behaviors)
    {
      weighted_force = rule->ComputeWeightedForce(neighbors, *boid);
      boid->apply_force(weighted_force);
    }
  }
}

static void draw(void)
{
  for (const auto &boid : Boid::all)
  {
    auto *self = boid.get();

    self->Draw();

    if (state.debug.show_acceleration)
    {
      constexpr int vector_length = 16.0f;
      Vector2f pos = self->get_position();
      Vector2f tmp = self->get_position() + self->get_velocity().normalized() * vector_length;
      engine::graphics::line(pos.x, pos.y, tmp.x, tmp.y);
    }

    if (state.debug.show_rules)
    {
      /* todo: draw a line from position to acceleration */
    }

    if (state.debug.show_radius)
    {
      auto x = self->get_position().x;
      auto y = self->get_position().y;
      auto r = self->get_radius();
      engine::graphics::set_color(1.0f, 1.0f, 1.0f, 1.0f);
      engine::graphics::circle(engine::graphics::DrawMode::DRAW_MODE_LINE, x, y, r);
    }
  }
}
static void gui(void)
{
  ImGui::Begin("Controlls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS", ImGui::GetIO().DeltaTime * 1000, 1.0f / ImGui::GetIO().DeltaTime, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  ImGui::Separator();
  ImGui::Checkbox("Show Radius", &state.debug.show_radius);
  ImGui::Checkbox("Show Rules", &state.debug.show_rules);
  ImGui::Checkbox("Show Acceleration", &state.debug.show_acceleration);

  ImGui::Separator();
  ImGui::Text("Time Controls");
  ImGui::Separator();
  ImGui::Checkbox("Paused", &state.time.paused);
  ImGui::SliderFloat("Time Factor", &state.time.factor, 0.0f, 10.0f, "%.1f", ImGuiSliderFlags_None);

  FlockingBehavior *temp;

  temp = &(*state.flocking_behaviors[2]);
  ImGui::Separator();
  ImGui::Checkbox("Enable Alignment", &temp->enabled);
  if (temp->enabled)
  {
    ImGui::PushID("alignment");
    ImGui::Separator();
    ImGui::DragFloat("Weight", &temp->weight, 0.025f, 0.0f, 100.0f);
    ImGui::PopID();
  }
  temp = &(*state.flocking_behaviors[1]);
  ImGui::Separator();
  ImGui::Checkbox("Enable Cohesion", &temp->enabled);
  if (temp->enabled)
  {
    ImGui::PushID("cohesion");
    ImGui::Separator();
    ImGui::DragFloat("Weight", &temp->weight, 0.025f, 0.0f, 100.0f);
    ImGui::PopID();
  }

  temp = &(*state.flocking_behaviors[0]);
  ImGui::Separator();
  ImGui::Checkbox("Enable Separation", &temp->enabled);
  if (temp->enabled)
  {
    ImGui::PushID("separation");
    ImGui::Separator();
    ImGui::DragFloat("Weight", &temp->weight, 0.025f, 0.0f, 100.0f);
    ImGui::PopID();
  }

  ImGui::End();
}

game_desc game_main(int argv, char *argc[])
{
  game_desc desc{
      .load_cb = load,
      .cleanup_cb = cleanup,
      .update_cb = update,
      .draw_cb = draw,
      .gui_cb = gui,
      .config = {
          .window = {
              .title = "Flocking",
              .width = 800,
              .height = 800,
          },
      },
  };
  return desc;
}