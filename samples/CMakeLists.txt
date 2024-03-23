cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(samples)

#=== setup
add_executable(setup setup.cpp)
target_link_libraries(setup dbgui)
target_link_libraries(setup engine)
target_compile_definitions(setup PRIVATE USE_DBG_UI)

#=== ant
add_executable(ant ant.cpp)
target_link_libraries(ant dbgui)
target_link_libraries(ant engine)

#=== behavioral_agent
add_executable(behavioral_agent behavioral_agent.cpp)
target_link_libraries(behavioral_agent dbgui)
target_link_libraries(behavioral_agent engine)

#=== hexagon
add_executable(hexagon hexagon.cpp)
target_link_libraries(hexagon dbgui)
target_link_libraries(hexagon engine)

#=== LINKER: emscripten
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  target_link_options(behavioral_agent PUBLIC -sUSE_WEBGL2=1 --shell-file ../../extra/shell.html)
endif()