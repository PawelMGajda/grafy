cmake_minimum_required(VERSION 3.14)
project(ok)

set(CMAKE_CXX_STANDARD 14)

add_executable(ok bellman_algorithms.cpp bellman_algorithms.h list_graph.cpp list_graph.h graph.h matrix_graph.cpp matrix_graph.h tests.cpp)