/* sokol */
#include "../sokol/sokol_gfx.h"
#include "../sokol/sokol_app.h"
#include "../sokol/sokol_glue.h"

/* imgui */
#include "../imgui/imgui.h"

#define SOKOL_IMGUI_IMPL
#include "../sokol/sokol_imgui.h"

extern "C"
{
  namespace
  {
    static struct
    {
      sg_pass_action pass_action;
    } state;
  }
  void __dbgui_setup(void)
  {
    simgui_setup((simgui_desc_t){0});
    state.pass_action = {
        .colors = {{.load_action = SG_LOADACTION_DONTCARE}},
    };
  }

  void __dbgui_shutdown(void)
  {
    simgui_shutdown();
  }

  void __dbgui_begin(void)
  {
    simgui_new_frame((simgui_frame_desc_t){
        .width = sapp_width(),
        .height = sapp_height(),
        .delta_time = sapp_frame_duration(),
        .dpi_scale = sapp_dpi_scale(),
    });
  }

  void __dbgui_end(void)
  {
    sg_begin_pass({.action = state.pass_action, .swapchain = sglue_swapchain()});
    simgui_render();
    sg_end_pass();
    sg_commit();
  }

  void __dbgui_event(const sapp_event *ev)
  {
    simgui_handle_event(ev);
  }
}