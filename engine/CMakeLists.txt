# what?
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
define_property(
  TARGET
  PROPERTY FOLDER
  INHERITED
  BRIEF_DOCS "Set the folder name."
  FULL_DOCS  "Use to organize targets in an IDE.")

set(COMMON_SRC)
set(COMMON_HEADERS
  common/color.h
  common/math.h
  common/matrix4.h
  common/quaternion.h
  common/vector2.h
  common/vector3.h
  common/vector4.h)

set(CORE_SRC
  engine/engine.cpp)
set(CORE_HEADERS
  engine/engine.h)

set(GRAPHICS_SRC
  graphics/graphics.cpp)
set(GRAPHICS_HEADERS
  graphics/graphics.h)

set(MATH_SRC
  math/math.cpp)
set(MATH_HEADERS
  math/math.h)

set(MOUSE_SRC
  mouse/mouse.cpp)
set(MOUSE_HEADERS
  mouse/mouse.h)

#=== LIBRARY: engine
set(ENGINE_SRC
  ${COMMON_SRC}
  ${CORE_SRC}
  ${GRAPHICS_SRC}
  ${MATH_SRC}
  ${MOUSE_SRC})
set(ENGINE_HEADERS
  ${COMMON_HEADERS}
  ${CORE_HEADERS}
  ${GRAPHICS_HEADERS}
  ${MATH_HEADERS}
  ${MOUSE_HEADERS})

add_library(engine STATIC platform.cpp ${ENGINE_SRC} ${ENGINE_HEADERS})
target_include_directories(engine PUBLIC . ../libs)

# privately linked libraries
target_link_libraries(engine PUBLIC sokol)
target_link_libraries(engine PUBLIC dbgui)
target_link_libraries(engine PUBLIC stb)

# publicly linked libraries
target_link_libraries(engine PUBLIC imgui)
target_link_libraries(engine PUBLIC batteries)