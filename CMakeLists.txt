cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(gpr340)

# macros
include("extra/cmake/macros.cmake")

# engine
include_directories(engine)
add_subdirectory(engine)
set_property(DIRECTORY engine PROPERTY FOLDER "engine")

# assignments
add_subdirectory(assignments)
set_property(DIRECTORY assignments PROPERTY FOLDER "assignments")