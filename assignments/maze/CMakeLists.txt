project(maze)

#=== EXECUTABLE: maze
set(MAZE_HEADERS
  # generators
  src/generators/huntandkill.h
  src/generators/mazegenerator.h
  src/generators/randomwalk.h
  src/generators/recursivebacktracker.h

  # rules
  src/world.h)

set(MAZE_SRC
  # generators
  src/generators/huntandkill.cpp
  src/generators/randomwalk.cpp
  src/generators/recursivebacktracker.cpp

  # rules
  src/world.cpp
  src/game.cpp)

add_executable(maze src/game.cpp ${MAZE_SRC} ${MAZE_HEADERS})

target_include_directories(maze INTERFACE maze)
target_link_libraries(maze engine)
target_link_libraries(maze imgui)
target_link_libraries(maze batteries)

emscripten(maze)