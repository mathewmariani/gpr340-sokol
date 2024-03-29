#=== EXECUTABLE: tower-defense
set(TOWERDEFENSE_HEADERS
  # heuristic
  src/heuristic/heuristic.h
  src/heuristic/manhattandistance.h

  # objects
  src/objects/goal.h
  src/objects/start.h
  src/objects/object.h

  # search
  src/search/astarsearch.h
  src/search/breadthfirstsearch.h
  src/search/dijkstrasearch.h
  src/search/greedysearch.h
  src/search/search.h

  # rules
  src/world.h)

set(TOWERDEFENSE_SRC
  # objects
  src/objects/goal.cpp
  src/objects/start.cpp

  # search
  src/search/astarsearch.cpp
  src/search/breadthfirstsearch.cpp
  src/search/dijkstrasearch.cpp
  src/search/greedysearch.cpp
  

  # rules
  src/world.cpp
  src/game.cpp)

add_executable(tower-defense src/game.cpp ${TOWERDEFENSE_SRC} ${TOWERDEFENSE_HEADERS})

target_include_directories(tower-defense INTERFACE tower-defense)
target_link_libraries(tower-defense PRIVATE engine)

emscripten(tower-defense)