add_executable(
    ${APP_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
target_include_directories(
    ${APP_NAME}
    PUBLIC
    /opt/ros/noetic/include
)
target_link_libraries(
    ${APP_NAME} PRIVATE
    local::app
)
set_target_properties(
    ${APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_subdirectory(app)
if (ENABLE_TEST)
    add_subdirectory(test)
endif()