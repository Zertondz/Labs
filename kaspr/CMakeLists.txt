cmake_minimum_required(VERSION 3.16)
project(BFG)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_CXX_STANDARD 20)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-DWIN32)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g  -fPIC -std=c++20 -O0") #--coverage
if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/json/include)
endif()

add_executable(BFGserv server/main.cpp)
add_executable(BFGclient client/main.cpp)
add_executable(BFGservGr serverGraph/main.cpp)
#add_executable(BFGtest test/tests.cpp)
if(WIN32)
    target_link_libraries(BFGclient ws2_32)
    target_link_libraries(BFGservGr ws2_32)
    target_link_libraries(BFGserv ws2_32)
endif()
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
#target_include_directories(BFGtest PRIVATE
#../kaspr/server
#../kaspr/serverGraph
#../kaspr/client
#../kaspr)

#find_package(GTest REQUIRED)
#include(GoogleTest)
#target_link_libraries(BFGtest GTest::GTest GTest::Main)
#gtest_discover_tests(BFGtest)