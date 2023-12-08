cmake_minimum_required(VERSION 3.9.1)

project(Gobang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(gobang SHARED src/board.cpp src/player.cpp src/game.cpp)

add_executable(main main.cpp)
target_link_libraries(main gobang)
