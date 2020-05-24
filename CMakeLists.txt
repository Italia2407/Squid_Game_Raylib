cmake_minimum_required(VERSION 3.0)
project(raylib_Squid_Game C)

set(CMAKE_C_STANDARD 99)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)

add_executable(raylib_Squid_Game src/main.c src/gameobject.h src/gameobject.c src/player.h src/player.c src/playercam.h src/playercam.c src/projectile.h src/projectile.c)
target_link_libraries(raylib_Squid_Game PRIVATE raylib)

target_compile_definitions(raylib_Squid_Game PRIVATE ASSET_PATH="../assets/") # the default folder path for all of our assets