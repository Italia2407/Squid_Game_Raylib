cmake_minimum_required(VERSION 3.0)
project(raylib_Squid_Game C)

set(CMAKE_C_STANDARD 99)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)

set(SRC_FILES src/main.c src/globals.c)
set(SRC_FILES_OBJ src/objects/gameobject.c src/objects/player.c src/objects/projectile.c)
set(SRC_FILES_MGT src/management/playercam.c src/management/spritemanager.c)

add_executable(raylib_Squid_Game ${SRC_FILES} ${SRC_FILES_OBJ} ${SRC_FILES_MGT})
target_link_libraries(raylib_Squid_Game PRIVATE raylib)