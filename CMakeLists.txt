cmake_minimum_required(VERSION 3.17)
project(comb CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(comb1 lab1/src/main.c)
add_executable(comb2 lab2/src/main.c)
add_executable(comb3 lab3/src/main.cpp)

add_executable(test manuals/examples/lab3/main.cpp manuals/examples/lab3/matrix.cpp)