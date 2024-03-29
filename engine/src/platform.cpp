/* sokol */
#include "sokol/sokol_app.h"

/* dbgui */
#include "dbgui/dbgui.h"

/* engine modules */
#include "engine/engine.h"
#include "graphics/graphics.h"
#include "math/math.h"
#include "mouse/mouse.h"

/* forward declarations for sokol */
static void init(void);
static void frame(void);
static void cleanup(void);
static void event(const sapp_event *, void *);

static game_desc _game;

engine::module_t modules;

#define _engine_def(val, def) (((val) == 0) ? (def) : (val))
#define _engine_def_flt(val, def) (((val) == 0.0f) ? (def) : (val))

/* TODO: this should be hidden in `engine/engine.cpp` */
static game_desc _config_desc_defaults(const game_desc *desc)
{
  game_desc def = *desc;
  def.config.window.width = _engine_def_flt(def.config.window.width, 800.0f);
  def.config.window.height = _engine_def_flt(def.config.window.height, 800.0f);
  def.config.window.title = _engine_def(def.config.window.title, "edu-engine");
  return def;
}

int main(int argc, char *argv[])
{
  _game = game_main(argc, argv);
  _config_desc_defaults(&_game);

  /* set defaults for description after calling the entry point */
  sapp_run((sapp_desc){
      .init_cb = init,
      .frame_cb = frame,
      .cleanup_cb = cleanup,
      .user_data = &modules,
      .event_userdata_cb = event,

      .width = _game.config.window.width,
      .height = _game.config.window.height,
      .window_title = _game.config.window.title,
  });
  return 0;
}

static void init(void)
{
  engine::graphics::setup();
  engine::math::setup();
  engine::mouse::setup();

  /* setup dbgui */
  if (_game.gui_cb)
  {
    __dbgui_setup();
  }

  /* always last */
  if (_game.load_cb)
  {
    _game.load_cb();
  }
}

static void cleanup(void)
{
  _game.cleanup_cb();
  if (_game.gui_cb)
  {
    __dbgui_shutdown();
  }
  /* always last */
  engine::graphics::cleanup();
  engine::math::cleanup();
  engine::mouse::cleanup();
}

static void frame(void)
{
  { /* update */
    if (_game.update_cb)
    {
      _game.update_cb((float)sapp_frame_duration());
    }
  }

  { /* draw */
    engine::graphics::clear();
    engine::graphics::origin();

    if (_game.draw_cb)
    {
      _game.draw_cb();
    }

    engine::graphics::present();
  }

  /* always last. */
  if (_game.gui_cb)
  {
    __dbgui_begin();
    _game.gui_cb();
    __dbgui_end();
  }
}

static void event(const sapp_event *ev, void *userdata)
{
  switch (ev->type)
  {
  // keyboard:
  case SAPP_EVENTTYPE_KEY_DOWN:
  {
  }
  break;

  case SAPP_EVENTTYPE_KEY_UP:
  {
  }
  break;

  // mouse:
  case SAPP_EVENTTYPE_MOUSE_MOVE:
  {
    /* update internal state */
    auto *m = (engine::module_t *)userdata;
    m->mouse.x = ev->mouse_x;
    m->mouse.y = ev->mouse_y;

    if (_game.mouse_moved_cb)
    {
      auto x = ev->mouse_x;
      auto y = ev->mouse_y;
      auto dx = ev->mouse_dx;
      auto dy = ev->mouse_dy;
      _game.mouse_moved_cb(x, y, dx, dy);
    }
  }
  break;

  case SAPP_EVENTTYPE_MOUSE_DOWN:
  {
    /* update internal state */
    auto *m = (engine::module_t *)userdata;
    m->mouse.is_down = true;

    if (_game.mouse_pressed_cb)
    {
      auto x = ev->mouse_x;
      auto y = ev->mouse_y;
      auto b = ev->mouse_button;
      _game.mouse_pressed_cb(x, y, (int)b);
    }
  }
  break;

  case SAPP_EVENTTYPE_MOUSE_UP:
  {
    /* update internal state */
    auto *m = (engine::module_t *)userdata;
    m->mouse.is_down = false;

    if (_game.mouse_released_cb)
    {
      auto x = ev->mouse_x;
      auto y = ev->mouse_y;
      auto b = ev->mouse_button;
      _game.mouse_released_cb(x, y, (int)b);
    }
  }
  break;

  default:
    break;
  }

  /* always last */
  if (_game.gui_cb)
  {
    __dbgui_event(ev);
  }
}