project(ants)

#=== EXECUTABLE: ants
set(ANTS_HEADERS
  )

set(ANTS_SRC
  src/game.cpp)

add_executable(ants src/game.cpp ${ANTS_SRC} ${ANTS_HEADERS})

target_include_directories(ants INTERFACE ants)
target_link_libraries(ants engine)
target_link_libraries(ants imgui)
target_link_libraries(ants batteries)

emscripten(ants)