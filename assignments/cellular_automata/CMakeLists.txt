#=== EXECUTABLE: cellular_automata
set(CELLULAR_AUTOMATA_HEADERS
  # rules
  src/rules/cavegeneration.h
  src/rules/johnconway.h
  src/rules/langtonsant.h
  src/rules/rockpaperscissors.h
  src/rules/rulebase.h

  src/world.h)

set(CELLULAR_AUTOMATA_SRC
  # rules
  src/rules/cavegeneration.cpp
  src/rules/johnconway.cpp
  src/rules/langtonsant.cpp
  src/rules/rockpaperscissors.cpp

  src/game.cpp
  src/world.cpp)

add_executable(cellular_automata src/game.cpp ${CELLULAR_AUTOMATA_SRC} ${CELLULAR_AUTOMATA_HEADERS})

target_include_directories(cellular_automata INTERFACE cellular_automata)
target_link_libraries(cellular_automata PRIVATE engine)

emscripten(cellular_automata)