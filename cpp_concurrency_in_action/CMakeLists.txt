cmake_minimum_required (VERSION 2.6)
project (learn_cpp_concurrency)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# boost thread
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS thread)

file (GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# add the executable
add_executable(${PROJECT_NAME} main.cc ${HEADERS})

if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()