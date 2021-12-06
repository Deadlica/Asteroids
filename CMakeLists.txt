cmake_minimum_required(VERSION 3.20)
project(sfml_game)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Game.cpp Game.h Player.cpp Player.h Object.cpp Object.h Asteroid.cpp Asteroid.h Projectile.cpp Projectile.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake-modules/")
find_package(SFML REQUIRED system window graphics network audio)

include_directories(${SFML_INCLUDE_DIR})

add_executable(sfml_game ${SOURCE_FILES})
target_link_libraries(sfml_game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})