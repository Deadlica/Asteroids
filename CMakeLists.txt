cmake_minimum_required(VERSION 3.20)
project(sfml_game)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp Game.cpp Game.h Player.cpp Player.h Object.cpp Object.h Asteroid.cpp Asteroid.h Projectile.cpp Projectile.h)

set(SFML_ROOT /usr/include/SFML)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(sfml_game ${SOURCE_FILES})
target_link_libraries(sfml_game sfml-system sfml-window sfml-graphics sfml-network sfml-audio)