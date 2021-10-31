cmake_minimum_required(VERSION 3.20)
project(BitCheckers)

set(CMAKE_CXX_STANDARD 23)

add_executable(BitCheckers main.cpp board.cpp board.h utility.cpp utility.h movegen.cpp movegen.h opponent.cpp opponent.h)
