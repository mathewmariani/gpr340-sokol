#=== EXECUTABLE: maze
set(MAZE_HEADERS
  # generators
  generators/huntandkill.h
  generators/mazegenerator.h
  generators/randomwalk.h
  generators/recursivebacktracker.h

  # rules
  world.h)

set(MAZE_SRC
  # generators
  generators/huntandkill.cpp
  generators/randomwalk.cpp
  generators/recursivebacktracker.cpp

  # rules
  world.cpp
  game.cpp)

add_executable(maze game.cpp ${MAZE_SRC} ${MAZE_HEADERS})

target_include_directories(maze INTERFACE maze)
target_link_libraries(maze PRIVATE engine)

emscripten(maze)