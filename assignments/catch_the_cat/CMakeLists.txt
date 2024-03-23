project(catch_the_cat)

#=== EXECUTABLE: catch_the_cat
set(CATCH_THE_CAT_HEADERS
  # agents
  src/agents/agent.h
  src/agents/cat.h
  src/agents/catcher.h

  src/world.h)

set(CATCH_THE_CAT_SRC
  # agents
  src/agents/agent.cpp
  src/agents/cat.cpp
  src/agents/catcher.cpp

  src/game.cpp
  src/world.cpp)

add_executable(catch_the_cat src/game.cpp ${CATCH_THE_CAT_SRC} ${CATCH_THE_CAT_HEADERS})

target_include_directories(catch_the_cat INTERFACE catch_the_cat)
target_link_libraries(catch_the_cat engine)
target_link_libraries(catch_the_cat imgui)
target_link_libraries(catch_the_cat batteries)

emscripten(catch_the_cat)