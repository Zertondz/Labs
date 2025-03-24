cmake_minimum_required(VERSION 3.16)
find_package(Catch2 3 REQUIRED)
# add_compile_options("")
# set the project name
project(dictionary)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "--coverage -Wall -Wextra -g  -fPIC -std=c++20")
add_executable(test_res Word.cpp tools.cpp Words.cpp tests.cpp tests_2.cpp)
add_executable(res main.cpp Word.cpp tools.cpp Words.cpp)

target_link_libraries(test_res PRIVATE Catch2::Catch2WithMain gcov)