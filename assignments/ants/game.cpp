// engine
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "mouse/mouse.h"
#include "libs/imgui/imgui.h"

#define STUBBED() \
  std::printf("[%s]\n", __FUNCTION__)

// forward declerations
static void load(void);
static void cleanup(void);
static void update(float);
static void draw(void);
static void mouse_pressed(float, float, int);
static void mouse_moved(float, float, float, float);
static void gui(void);

game_desc game_main(int argv, char *argc[])
{
  game_desc desc{
      .load_cb = load,
      .cleanup_cb = cleanup,
      .update_cb = update,
      .draw_cb = draw,
      .gui_cb = gui,
      .mouse_pressed_cb = mouse_pressed,
      .mouse_moved_cb = mouse_moved,
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
  STUBBED();
}

static void draw(void)
{
  STUBBED();
}

static void gui()
{
  STUBBED();
}

static void mouse_pressed(float x, float y, int button)
{
  STUBBED();
}

static void mouse_moved(float x, float y, float dx, float dy)
{
  STUBBED();
}