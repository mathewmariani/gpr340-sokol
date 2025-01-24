cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRDPARTY_DIR libs)
set(ASSIGNMENTS_DIR assignments)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/assignments")

project(gpr340)

# macros
include("extra/cmake/macros.cmake")
include("extra/cmake/batteries.cmake")
include("extra/cmake/dbgui.cmake")
include("extra/cmake/glm.cmake")
include("extra/cmake/imgui.cmake")
include("extra/cmake/sokol.cmake")
include("extra/cmake/stb.cmake")

include_directories(${THIRDPARTY_DIR})

# engine
add_subdirectory(engine)
set_property(DIRECTORY engine PROPERTY FOLDER "engine")

# assignments
add_subdirectory(assignments)
set_property(DIRECTORY assignments PROPERTY FOLDER "assignments")

# symlinks
execute_process(
  COMMAND ${CMAKE_COMMAND} -E create_symlink
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}"
  "${CMAKE_CURRENT_SOURCE_DIR}/website/public/demos")
