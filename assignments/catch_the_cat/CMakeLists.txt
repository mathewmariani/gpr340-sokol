#=== EXECUTABLE: catch_the_cat
set(CATCH_THE_CAT_HEADERS
  # agents
  agents/agent.h
  agents/cat.h
  agents/catcher.h

  world.h)

set(CATCH_THE_CAT_SRC
  # agents
  agents/agent.cpp
  agents/cat.cpp
  agents/catcher.cpp

  game.cpp
  world.cpp)

add_executable(catch_the_cat game.cpp ${CATCH_THE_CAT_SRC} ${CATCH_THE_CAT_HEADERS})

target_include_directories(catch_the_cat INTERFACE catch_the_cat)
target_link_libraries(catch_the_cat PRIVATE engine)

emscripten(catch_the_cat)