project(app)
file(
    GLOB_RECURSE OBJ_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
)
add_library(
    ${PROJECT_NAME}
    STATIC
    ${OBJ_SRCS}
)
add_library( 
    local::${PROJECT_NAME}
    ALIAS
    ${PROJECT_NAME}
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(httplib REQUIRED)
find_package(fmt REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Threads::Threads
    spdlog::spdlog
    httplib::httplib
    fmt::fmt
    nlohmann_json::nlohmann_json
    yaml-cpp
)