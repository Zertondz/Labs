cmake_minimum_required(VERSION 3.16)
project(BFG)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g  -fPIC -std=c++20 -O0") #--coverage
add_executable(BFGserv server/main.cpp)
add_executable(BFGclient client/main.cpp)
add_executable(BFGservGr serverGraph/main.cpp)
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