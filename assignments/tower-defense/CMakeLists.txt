#=== EXECUTABLE: tower-defense
set(TOWERDEFENSE_HEADERS
  # heuristic
  heuristic/heuristic.h
  heuristic/manhattandistance.h

  # objects
  objects/goal.h
  objects/start.h
  objects/object.h

  # search
  search/astarsearch.h
  search/breadthfirstsearch.h
  search/dijkstrasearch.h
  search/greedysearch.h
  search/search.h

  # rules
  world.h)

set(TOWERDEFENSE_SRC
  # objects
  objects/goal.cpp
  objects/start.cpp

  # search
  search/astarsearch.cpp
  search/breadthfirstsearch.cpp
  search/dijkstrasearch.cpp
  search/greedysearch.cpp
  

  # rules
  world.cpp
  game.cpp)

add_executable(tower-defense game.cpp ${TOWERDEFENSE_SRC} ${TOWERDEFENSE_HEADERS})

target_include_directories(tower-defense INTERFACE tower-defense)
target_link_libraries(tower-defense PRIVATE engine)

emscripten(tower-defense)