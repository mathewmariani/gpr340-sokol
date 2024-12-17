cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(samples)

#=== setup
add_executable(setup setup.cpp)
target_link_libraries(setup engine)

#=== ant
add_executable(ant ant.cpp)
target_link_libraries(ant engine)

#=== behavioral_agent
add_executable(behavioral_agent behavioral_agent.cpp)
target_link_libraries(behavioral_agent engine)

#=== hexagon
add_executable(hexagon hexagon.cpp)
target_link_libraries(hexagon engine)