project(flocking)

#=== EXECUTABLE: flocking
set(FLOCKING_HEADERS
  # agents
  src/agents/boid.h

  # behaviors
  src/behaviors/alignment.h
  src/behaviors/boundingbox.h
  src/behaviors/cohesion.h
  src/behaviors/flockingbehavior.h
  src/behaviors/mouseinfluence.h
  src/behaviors/separation.h)

set(FLOCKING_SRC
  src/game.cpp

  # agents
  src/agents/boid.cpp
  
  # behaviors
  src/behaviors/alignment.cpp
  src/behaviors/boundingbox.cpp
  src/behaviors/cohesion.cpp
  src/behaviors/mouseinfluence.cpp
  src/behaviors/separation.cpp)

add_executable(flocking src/game.cpp ${FLOCKING_SRC} ${FLOCKING_HEADERS})

target_include_directories(flocking INTERFACE flocking)
target_link_libraries(flocking engine)
target_link_libraries(flocking imgui)

emscripten(flocking)