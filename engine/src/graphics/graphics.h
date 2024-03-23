#pragma once

#include "common/color.h"
#include "common/vector2.h"

namespace engine
{
  namespace graphics
  {
    enum class DrawMode
    {
      DRAW_MODE_LINE,
      DRAW_MODE_FILL,
      DRAW_MODE_MAX_ENUM,
    };

    void setup(void);
    void cleanup(void);

    void get_dimensions(int *width, int *height);

    void set_color(Colorf c);
    void set_color(float r, float g, float b, float a);

    void points(const Vector2f *points, int size);
    void line(float x0, float x1, float y0, float y1);
    void polyline(const Vector2f *coords, int size);
    void polygon(const DrawMode mode, const Vector2f *coords, int size);
    void ellipse(const DrawMode mode, float x, float y, float a, float b, int segments);
    void circle(const DrawMode mode, float x, float y, float radius);
    void rectangle(const DrawMode mode, float x, float y, float width, float height);

    void clear(void);
    void present(void);

    /* coordinate system */
    void push_transform(void);
    void pop_transform(void);
    void origin(void);
    void pop(void);
    void push(void);
    void translate(float dx, float dy);
    void rotate(float angle);
  }
}