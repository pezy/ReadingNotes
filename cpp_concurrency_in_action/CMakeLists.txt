cmake_minimum_required (VERSION 2.6)
project (cpp_concurrency_in_action)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add the executable
add_executable(cpp_concurrency_in_action main.cc)