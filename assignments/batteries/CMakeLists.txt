set(BATTERIES_FILES
    agent.h
    cellgrid.h
    colors.h
    finite_grid.h
    graph.h
    grid_location.h
    grid.h
    hexgrid.h
    node.h)

add_library(batteries INTERFACE ${BATTERIES_FILES})