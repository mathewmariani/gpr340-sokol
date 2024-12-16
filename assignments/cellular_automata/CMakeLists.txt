#=== EXECUTABLE: cellular_automata
set(CELLULAR_AUTOMATA_HEADERS
  # rules
  rules/cavegeneration.h
  rules/johnconway.h
  rules/langtonsant.h
  rules/rockpaperscissors.h
  rules/rulebase.h

  world.h)

set(CELLULAR_AUTOMATA_SRC
  # rules
  rules/cavegeneration.cpp
  rules/johnconway.cpp
  rules/langtonsant.cpp
  rules/rockpaperscissors.cpp

  game.cpp
  world.cpp)

add_executable(cellular_automata game.cpp ${CELLULAR_AUTOMATA_SRC} ${CELLULAR_AUTOMATA_HEADERS})

target_include_directories(cellular_automata INTERFACE cellular_automata)
target_link_libraries(cellular_automata PRIVATE engine)

emscripten(cellular_automata)