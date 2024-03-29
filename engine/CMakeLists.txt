project(engine)

add_definitions(-DSOKOL_NO_ENTRY)
# platform selection
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
  add_definitions(-DSOKOL_GLES3)
elseif (CMAKE_SYSTEM_NAME STREQUAL Darwin)
  add_definitions(-DSOKOL_GLCORE33)
endif()

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
  src/common/color.h
  src/common/math.h
  src/common/matrix4.h
  src/common/quaternion.h
  src/common/vector2.h
  src/common/vector3.h
  src/common/vector4.h)

set(CORE_SRC
  src/engine/engine.cpp)
set(CORE_HEADERS
  src/engine/engine.h)

set(GRAPHICS_SRC
  src/graphics/graphics.cpp)
set(GRAPHICS_HEADERS
  src/graphics/graphics.h)

set(MATH_SRC
  src/math/math.cpp)
set(MATH_HEADERS
  src/math/math.h)

set(MOUSE_SRC
  src/mouse/mouse.cpp)
set(MOUSE_HEADERS
  src/mouse/mouse.h)

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

include_directories(libs)
add_subdirectory(libs)

add_library(engine STATIC src/platform.cpp ${ENGINE_SRC} ${ENGINE_HEADERS})
target_include_directories(engine PUBLIC src libs)

target_link_libraries(engine PRIVATE sokol)
target_link_libraries(engine PRIVATE dbgui)
target_link_libraries(engine PRIVATE stb)
target_link_libraries(engine PUBLIC imgui)
target_link_libraries(engine PUBLIC batteries)
