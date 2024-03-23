#pragma once

namespace engine
{
  namespace mouse
  {
    enum class mouse_cursor
    {
      MOUSECURSOR_DEFAULT = 0,
      MOUSECURSOR_ARROW,
      MOUSECURSOR_IBEAM,
      MOUSECURSOR_CROSSHAIR,
      MOUSECURSOR_POINTING_HAND,
      MOUSECURSOR_RESIZE_EW,
      MOUSECURSOR_RESIZE_NS,
      MOUSECURSOR_RESIZE_NWSE,
      MOUSECURSOR_RESIZE_NESW,
      MOUSECURSOR_RESIZE_ALL,
      MOUSECURSOR_NOT_ALLOWED,
      MOUSECURSOR_NUM,
    };

    void setup(void);
    void cleanup(void);

    bool is_down(void);
    float get_x(void);
    float get_y(void);

    void set_cursor(mouse_cursor cursor);
  }
}