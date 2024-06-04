cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)
project(snakeworld LANGUAGES C)
add_executable(snakeworld)

# Util
function(add_git_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG        ${gitTag}
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(${libName})
    target_compile_options(${libName} PRIVATE "-w")
endfunction()

#

# Raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
add_git_dependency(
    raylib
    https://github.com/raysan5/raylib.git
    5.0
)

# Lua
find_package(Lua REQUIRED)

target_compile_features(snakeworld PRIVATE c_std_17)

target_include_directories(snakeworld PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${LUA_INCLUDE_DIR}
)

target_sources(snakeworld PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/snake.c
    ${CMAKE_SOURCE_DIR}/src/game_math.c
    ${CMAKE_SOURCE_DIR}/src/resources.c
    ${CMAKE_SOURCE_DIR}/src/scenes/menu.c
    ${CMAKE_SOURCE_DIR}/src/scenes/game.c
    ${CMAKE_SOURCE_DIR}/src/scenes/scene.c
    ${CMAKE_SOURCE_DIR}/src/scenes/end_game.c
)

target_link_libraries(snakeworld PRIVATE
    raylib
    ${LUA_LIBRARIES}
)
