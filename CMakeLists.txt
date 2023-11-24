# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

cmake_minimum_required(VERSION 3.26)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set PROJECT_SOURCE_DIR to `src` directory of project
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/)

# make PROJECT_SOURCES a list of all the .cpp and .hpp files contained in PROJECT_SOURCE_DIR
file(GLOB PROJECT_SOURCES
    "${PROJECT_SOURCE_DIR}/*.cpp" # add all source files
    "${PROJECT_SOURCE_DIR}/*.hpp" # add all header files
    )

# make an executable from all PROJECT_SOURCES
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# link raylib to executable
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# target to copy assets from CMAKE_SOURCE_DIR/resources to CMAKE_BINARY_DIR/resources
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)

# make `assets` target required to compile project
add_dependencies(game assets)
