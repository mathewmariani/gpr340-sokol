set(BUILD_WITH_BATTERIES_DEFAULT TRUE)

option(BUILD_WITH_BATTERIES "batteries Enabled" ${BUILD_WITH_BATTERIES_DEFAULT})
message("BUILD_WITH_BATTERIES: ${BUILD_WITH_BATTERIES}")

if(BUILD_WITH_BATTERIES)
  set(BATTERIES_DIR ${THIRDPARTY_DIR}/batteries)
  set(BATTERIES_FILES
    ${BATTERIES_DIR}/agent.h
    ${BATTERIES_DIR}/finite_grid.h
    ${BATTERIES_DIR}/grid_location.h
    ${BATTERIES_DIR}/hexgrid.h
    ${BATTERIES_DIR}/hexgrid_location.h)

  add_library(batteries STATIC ${BATTERIES_FILES})
  # target_include_directories(batteries INTERFACE ${BATTERIES_DIR})

  target_link_libraries(batteries PRIVATE glm)
  target_link_libraries(batteries PRIVATE sokol)
endif()