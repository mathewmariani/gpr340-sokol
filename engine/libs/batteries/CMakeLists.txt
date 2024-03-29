set(BATTERIES_FILES
    agent.h
    cellgrid.h
    finite_grid.h
    graph.h
    grid_location.h
    grid.h
    hexgrid.h
    node.h)

# add_library(batteries STATIC )
add_library(batteries INTERFACE ${BATTERIES_FILES})
target_include_directories(batteries INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})