set(DBGUI_FILES
    dbgui.cpp
    dbgui.h)

add_library(dbgui ${DBGUI_FILES})
target_link_libraries(dbgui imgui)
target_link_libraries(dbgui sokol)