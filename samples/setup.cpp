/* engine */
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "imgui/imgui.h"

#define STUBBED() \
  std::printf("[%s]\n", __FUNCTION__)

static void load(void);
static void cleanup(void);
static void update(float);
static void draw(void);
static void gui(void);

/* mouse callbacks */
static void mouse_pressed(float, float, int);
static void mouse_released(float, float, int);
static void mouse_moved(float, float, float, float);

game_desc game_main(int argv, char *argc[])
{
  game_desc desc{
      .load_cb = load,
      .cleanup_cb = cleanup,
      .update_cb = update,
      .draw_cb = draw,
      .gui_cb = gui,
      .mouse_pressed_cb = mouse_pressed,
      .mouse_released_cb = mouse_released,
      .mouse_moved_cb = mouse_moved,
      .config = {
          .window = {
              .title = "Setup",
              .width = 800,
              .height = 800,
          },
      },
  };
  return desc;
}
static void load(void)
{
  STUBBED();
}
static void cleanup(void)
{
  STUBBED();
}
static void update(float dt)
{
}
static void draw(void)
{
}
static void gui()
{
  ImGui::SetNextWindowPos(ImVec2(460, 20), ImGuiCond_FirstUseEver);
  ImGui::ShowDemoWindow();
}
static void mouse_pressed(float x, float y, int button)
{
  STUBBED();
}
static void mouse_released(float x, float y, int button)
{
  STUBBED();
}
static void mouse_moved(float x, float y, float dx, float dy)
{
  STUBBED();
}