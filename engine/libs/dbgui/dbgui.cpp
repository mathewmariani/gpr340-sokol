/* sokol */
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_app.h"

/* imgui */
#include "imgui/imgui.h"

#define SOKOL_IMGUI_IMPL
#include "sokol/sokol_imgui.h"

extern "C"
{
  namespace
  {
    static struct
    {
      /* sokol resources */
      sg_context sg_ctx;
      sg_pass_action pass_action;
      int width;
      int height;
    } state;
  }
  void __dbgui_setup(void)
  {
    /* setup context */
    state.sg_ctx = sg_setup_context();
    sg_activate_context(state.sg_ctx);

    state.width = sapp_width();
    state.height = sapp_height();

    // default options
    simgui_desc_t simgui_desc{0};
    simgui_setup(&simgui_desc);

    state.pass_action = {
        .colors = {
            {
                .load_action = SG_LOADACTION_DONTCARE,
            },
        },
    };
  }

  void __dbgui_shutdown(void)
  {
    simgui_shutdown();
    sg_discard_context(state.sg_ctx);
  }

  void __dbgui_begin(void)
  {
    sg_activate_context(state.sg_ctx);
    simgui_frame_desc_t desc = {
        .width = state.width,
        .height = state.height,
        .delta_time = sapp_frame_duration(),
        .dpi_scale = sapp_dpi_scale(),
    };
    simgui_new_frame(&desc);
  }

  void __dbgui_end(void)
  {
    sg_begin_default_pass(&state.pass_action, state.width, state.height);
    simgui_render();
    sg_end_pass();
    sg_commit();
  }

  void __dbgui_event(const sapp_event *ev)
  {
    simgui_handle_event(ev);
  }
}