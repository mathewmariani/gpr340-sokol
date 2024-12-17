#include "mouse.h"
#include "engine/engine.h"

// sokol
#include "sokol/sokol_app.h"

#include <unordered_map>

#define instance() (((engine::module_t *)sapp_userdata())->mouse);

namespace engine
{
  namespace mouse
  {
    void setup(void)
    {
    }

    void cleanup(void)
    {
    }

    bool is_down(void)
    {
      auto mouse = ((engine::module_t *)sapp_userdata())->mouse;
      return mouse.is_down;
    }
    float get_x(void)
    {
      auto mouse = ((engine::module_t *)sapp_userdata())->mouse;
      return mouse.x;
    }
    float get_y(void)
    {
      auto mouse = ((engine::module_t *)sapp_userdata())->mouse;
      return mouse.y;
    }

    static std::unordered_map<mouse_cursor, sapp_mouse_cursor> cursors_map{
        {mouse_cursor::MOUSECURSOR_DEFAULT, SAPP_MOUSECURSOR_DEFAULT},
        {mouse_cursor::MOUSECURSOR_ARROW, SAPP_MOUSECURSOR_ARROW},
        {mouse_cursor::MOUSECURSOR_IBEAM, SAPP_MOUSECURSOR_IBEAM},
        {mouse_cursor::MOUSECURSOR_CROSSHAIR, SAPP_MOUSECURSOR_CROSSHAIR},
        {mouse_cursor::MOUSECURSOR_POINTING_HAND, SAPP_MOUSECURSOR_POINTING_HAND},
        {mouse_cursor::MOUSECURSOR_RESIZE_EW, SAPP_MOUSECURSOR_RESIZE_EW},
        {mouse_cursor::MOUSECURSOR_RESIZE_NS, SAPP_MOUSECURSOR_RESIZE_NS},
        {mouse_cursor::MOUSECURSOR_RESIZE_NWSE, SAPP_MOUSECURSOR_RESIZE_NWSE},
        {mouse_cursor::MOUSECURSOR_RESIZE_NESW, SAPP_MOUSECURSOR_RESIZE_NESW},
        {mouse_cursor::MOUSECURSOR_RESIZE_ALL, SAPP_MOUSECURSOR_RESIZE_ALL},
        {mouse_cursor::MOUSECURSOR_NOT_ALLOWED, SAPP_MOUSECURSOR_NOT_ALLOWED},
    };

    void set_cursor(mouse_cursor cursor)
    {
      sapp_set_mouse_cursor(cursors_map[cursor]);
    }
  }
}