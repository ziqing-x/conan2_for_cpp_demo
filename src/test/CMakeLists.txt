project(test_${APP_NAME})

file(
    GLOB_RECURSE TEST_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

find_package(doctest REQUIRED)

add_executable(
    ${PROJECT_NAME} ${TEST_SRCS}
)
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    local::app
    doctest::doctest
)