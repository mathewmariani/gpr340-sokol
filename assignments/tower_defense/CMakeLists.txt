#=== EXECUTABLE: tower_defense
set(TOWERDEFENSE_HEADERS
  # heuristic
  heuristic/heuristic.h
  heuristic/manhattandistance.h

  # objects
  objects/goal.h
  objects/start.h
  objects/object.h

  # rules
  pathfinding.h)

set(TOWERDEFENSE_SRC
  # objects
  objects/goal.cpp
  objects/start.cpp

  # search
  # search/astarsearch.cpp
  search/breadthfirstsearch.cpp
  # search/dijkstrasearch.cpp
  # search/greedysearch.cpp
  
  # rules
  game.cpp)

add_executable(tower_defense game.cpp ${TOWERDEFENSE_SRC} ${TOWERDEFENSE_HEADERS})

target_include_directories(tower_defense INTERFACE tower_defense)
target_link_libraries(tower_defense PRIVATE engine)

emscripten(tower_defense)