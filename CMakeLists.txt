cmake_minimum_required(VERSION 3.25)
project(GraphBattle)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GraphBattle
        FormRec.cpp main.cpp)
