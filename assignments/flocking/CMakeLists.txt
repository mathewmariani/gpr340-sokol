#=== EXECUTABLE: flocking
set(FLOCKING_HEADERS
  # agents
  agents/boid.h

  # behaviors
  behaviors/alignment.h
  behaviors/boundingbox.h
  behaviors/cohesion.h
  behaviors/flockingbehavior.h
  behaviors/mouseinfluence.h
  behaviors/separation.h)

set(FLOCKING_SRC
  game.cpp

  # agents
  agents/boid.cpp
  
  # behaviors
  behaviors/alignment.cpp
  behaviors/boundingbox.cpp
  behaviors/cohesion.cpp
  behaviors/mouseinfluence.cpp
  behaviors/separation.cpp)

add_executable(flocking game.cpp ${FLOCKING_SRC} ${FLOCKING_HEADERS})

target_include_directories(flocking INTERFACE flocking)
target_link_libraries(flocking PRIVATE engine)

emscripten(flocking)