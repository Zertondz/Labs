cmake_minimum_required(VERSION 3.16)
project(BFG)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g  -fPIC -std=c++20 -O0") #--coverage
add_executable(BFGserv server/main.cpp)
add_executable(BFGclient client/main.cpp)
add_executable(BFGservGr serverGraph/main.cpp)
add_executable(BFGtest test/tests.cpp)
target_include_directories(BFGserv PRIVATE
../kaspr/server
../kaspr/serverGraph
../kaspr/client
../kaspr)
target_include_directories(BFGclient PRIVATE
../kaspr/server
../kaspr/serverGraph
../kaspr/client
../kaspr)
target_include_directories(BFGservGr PRIVATE
../kaspr/server
../kaspr/serverGraph
../kaspr/client
../kaspr)
target_include_directories(BFGtest PRIVATE
../kaspr/server
../kaspr/serverGraph
../kaspr/client
../kaspr)

find_package(GTest REQUIRED)
include(GoogleTest)
target_link_libraries(BFGtest GTest::GTest GTest::Main)
gtest_discover_tests(BFGtest)