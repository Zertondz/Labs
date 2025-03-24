cmake_minimum_required(VERSION 3.16)
find_package(Catch2 3 REQUIRED)
# add_compile_options("")
# set the project name
project(dictionary)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g --coverage -fPIC ")
set(CMAKE_CXX_COMPILER "g++-13")
# add the executablec
add_executable(test_vini testini.cpp toolsini.cpp)
add_executable(res main.cpp toolsini.cpp dialini.cpp)
target_link_libraries(test_vini PRIVATE Catch2::Catch2WithMain gcov)