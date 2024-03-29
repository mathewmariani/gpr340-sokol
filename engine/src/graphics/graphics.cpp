/* sokol */
#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gl.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_log.h"

/* engine */
#include "engine/engine.h"
#include "graphics.h"
#include "common/math.h"

#include "common/vector2.h"
#include "common/vector3.h"
#include "common/matrix4.h"

#include <vector>
#include <stack>

namespace
{
  static struct
  {
    sg_pass_action pass_action;
    sgl_pipeline pip;
    // sg_context ctx;

    float width;
    float height;

    std::stack<Matrix4f> matrix_stack;

    // TODO: matrix stack with custom matrix function
  } state;
}

namespace engine
{
  namespace graphics
  {
    void setup(void)
    {
      /* setup sokol_gfx */
      sg_setup((sg_desc){
          .environment = sglue_environment(),
          .logger.func = slog_func,
      });

      /* create graphics module context */
      // state.ctx = sg_setup_context();
      // sg_activate_context(state.ctx);

      /* setup sokol-gl */
      sgl_desc_t sgldesc{0};
      sgl_setup(&sgldesc);

      /* setup our own internal graphics painter */
      state.width = (float)sapp_width();
      state.height = (float)sapp_height();

      /* clear to black */
      state.pass_action = {
          .colors = {
              {
                  .load_action = SG_LOADACTION_CLEAR,
                  .clear_value = {0.0f, 0.0f, 0.0f, 1.0f},
              },
          },
      };

      /* pipeline */
      sg_pipeline_desc pipdesc{
          .colors = {
              {
                  .blend = {
                      .enabled = true,
                      .src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA,
                      .dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
                  },
              },
          },
      };
      state.pip = sgl_make_pipeline(&pipdesc);

      /* init graphics state*/
      sgl_defaults();
      sgl_push_pipeline();
      sgl_load_pipeline(state.pip);

      /* initialize sokol matrix */
      sgl_matrix_mode_projection();
      sgl_ortho(0.0f, state.width, state.height, 0.0f, -10.0f, +10.0f);

      /* initialize internal matrix */
      push_transform();
    }

    void cleanup(void)
    {
      // sg_activate_context(state.ctx);
      sgl_destroy_pipeline(state.pip);
      sgl_shutdown();
      // sg_discard_context(state.ctx);
      sg_shutdown();
    }

    void get_dimensions(int *width, int *height)
    {
      auto graphics = ((engine::module_t *)sapp_userdata())->graphics;
      *width = (int)state.width;
      *height = (int)state.height;
    }

    void set_color(Colorf c)
    {
      set_color(c.r, c.g, c.b, c.a);
    }

    void set_color(float r, float g, float b, float a)
    {
      sgl_c4f(r, g, b, a);
    }

    void points(const Vector2f *points, int size)
    {
      if ((size & 1) == 0)
      {
        return;
      }

      Vector2f *a, *b;
      sgl_begin_points();
      for (auto i = 0; i < size - 1; ++i)
      {
        a = (Vector2f *)(points + i + 0);
        b = (Vector2f *)(points + i + 1);
        sgl_v2f(a->x, a->y);
        sgl_v2f(b->x, b->y);
      }
      sgl_end();
    }

    void line(float x0, float y0, float x1, float y1)
    {
      /* TODO: draw lines as smol rectangles */
      // std::vector<Vector2f> points{{x0, y0}, {x1, y1}};
      // polyline(&points[0], 2);
    }

    void polyline(const Vector2f *coords, int size)
    {
      auto t = state.matrix_stack.top();
      t.transformXY((Vector2f *)coords, size);

      /* FIXME: polyline should automatically loop */

      Vector2f *a, *b;
      sgl_begin_lines();
      for (auto i = 0; i < size - 1; ++i)
      {
        a = (Vector2f *)(coords + i + 0);
        b = (Vector2f *)(coords + i + 1);
        sgl_v2f(a->x, a->y);
        sgl_v2f(b->x, b->y);
      }
      sgl_end();
    }

    void polygon(const DrawMode mode, const Vector2f *coords, int size)
    {
      if (mode == DrawMode::DRAW_MODE_LINE)
      {
        polyline(coords, size);
        return;
      }

      const auto t = state.matrix_stack.top();
      t.transformXY((Vector2f *)coords, size);

      sgl_begin_triangle_strip();
      for (auto i = 0; i < size; ++i)
      {
        auto v = (coords + i);
        sgl_v2f(v->x, v->y);
      }
      sgl_end();
    }

    void ellipse(const DrawMode mode, float x, float y, float a, float b, int segments)
    {
      const auto tau = (float)(ENGINE_PI * 2.0f);
      const auto angle_shift = (tau / segments);
      auto phi = 0.0f;

      const auto extra_points = 1 + ((mode == DrawMode::DRAW_MODE_FILL) ? (1 + segments * 2) : 0);

      std::vector<Vector2f> buffer;
      buffer.reserve(segments + extra_points);
      Vector2f *coords = buffer.data();

      if (mode == DrawMode::DRAW_MODE_FILL)
      {
        coords[0].x = x;
        coords[0].y = y;
        coords++;

        for (auto i = 0; i < segments + extra_points; ++i, phi += angle_shift)
        {
          coords[i].x = x + a * cos(phi);
          coords[i].y = y + b * sin(phi);
          coords[++i] = coords[0];
        }
        coords[segments + extra_points] = coords[1];
        polygon(mode, coords, segments + extra_points);
      }
      else
      {
        for (auto i = 0; i < segments; ++i, phi += angle_shift)
        {
          coords[i].x = x + a * cos(phi);
          coords[i].y = y + b * sin(phi);
        }
        coords[segments] = coords[0];
        polyline(coords, segments + extra_points);
      }
    }

    void circle(const DrawMode mode, float x, float y, float radius)
    {
      ellipse(mode, x, y, radius, radius, 8);
    }

    void rectangle(const DrawMode mode, float x, float y, float width, float height)
    {
      /* parameters */
      const auto x0 = x;
      const auto x1 = x + width;
      const auto y0 = y;
      const auto y1 = y + height;

      Vector2f coords[] = {
          {x0, y0},
          {x1, y0},
          {x1, y1},
          {x0, y1},
          {x0, y0},
      };

      polygon(mode, coords, 5);
    }

    void clear(void)
    {
      // sg_activate_context(state.ctx);
      // sgl_defaults();

      /* render the sokol-gfx default pass */
      sg_begin_pass({.action = state.pass_action, .swapchain = sglue_swapchain()});
    }

    void present(void)
    {
      sgl_draw();
      sg_end_pass();
      sg_commit();
    }

    /* coordinate system */
    void origin(void)
    {
      // FIXME: I dont know why we have to call this every frame...
      sgl_matrix_mode_projection();
      sgl_ortho(0.0f, (float)state.width, (float)state.height, 0.0f, -1.0f, +1.0f);
      auto &t = state.matrix_stack.top();
      t.setIdentity();
    }
    void push_transform(void)
    {
      state.matrix_stack.push(Matrix4f::identity());
    }
    void push(void)
    {
      push_transform();
    }
    void pop_transform(void)
    {
      // TODO: this throws an error, we just catch it
      state.matrix_stack.pop();
    }
    void pop(void)
    {
      pop_transform();
    }
    void translate(float dx, float dy)
    {
      auto &t = state.matrix_stack.top();
      t.translate(dx, dy, 0.0f);
    }
    void rotate(float angle)
    {
      auto &t = state.matrix_stack.top();
      t.rotateZ(angle);
    }
  }
}