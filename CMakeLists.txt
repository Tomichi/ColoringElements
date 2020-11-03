project("ColoringElements")
cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")

add_subdirectory(src)
add_subdirectory(libs/google)
add_subdirectory(tests)
