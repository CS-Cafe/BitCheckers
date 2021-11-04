cmake_minimum_required(VERSION 3.20)
project(BitCheckers)

set(CMAKE_CXX_STANDARD 23)

add_executable(BitCheckers src/main.cpp src/board.cpp src/board.h src/utility.cpp src/utility.h src/movegen.cpp src/movegen.h src/opponent.cpp src/opponent.h src/move.h)
