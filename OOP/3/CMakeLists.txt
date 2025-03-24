cmake_minimum_required(VERSION 3.16)
set(SFML_DIR "/usr/lib/x86_64-linux-gnu/cmake/SFML")
# find_package(Catch2 3 REQUIRED)
# find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)
# add_compile_options("")
# set the project name
project(BFG)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g  -fPIC -std=c++20 -O0") #--coverage
add_library(my_library SHARED shared/Smart.cpp shared/Oper.cpp shared/Wild.cpp shared/Forager.cpp shared/Entity.cpp)
target_include_directories(my_library PUBLIC ../3/shared
../3/inventory/Item
../3/inventory
../3/level
../3/level/cell
../3/Vector
../3/game_algorithm
../3/entyties
../3/entyties/Entity
../3/Factories
../3/grafic
../3/logic_Dire
../3/shared)
set_target_properties(my_library PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(my_library sfml-graphics sfml-window sfml-system)
add_executable(res main.cpp level/cell/Cell.cpp inventory/Item/Item.cpp 
inventory/inventory.cpp   
game_algorithm/game_algorithm.cpp level/Level.cpp 
grafic/gravic.cpp logic_Dire/logicDire.cpp logic_Dire/logicDire_multi_thread.cpp)

target_include_directories(res PRIVATE 
../3/inventory/Item
../3/inventory
../3/level
../3/level/cell
../3/Vector
../3/game_algorithm
../3/entyties
../3/entyties/Entity
../3/Factories
../3/grafic
../3/logic_Dire
../3/shared)
target_link_libraries(res my_library sfml-graphics sfml-window sfml-system)
# add_executable(test_invent inventory/Item/Item.cpp 
# inventory/inventory.cpp tests/test_inventory.cpp game_algorithm/game_algorithm.cpp level/cell/Cell.cpp)
# add_executable(test_entity inventory/Item/Item.cpp 
# inventory/inventory.cpp tests/test_entity.cpp game_algorithm/game_algorithm.cpp level/cell/Cell.cpp
# entyties/Entity/Entity.cpp entyties/Forager.cpp entyties/Oper.cpp entyties/Smart.cpp entyties/Wild.cpp 
# level/Level.cpp)
# add_executable(test_level level/cell/Cell.cpp inventory/Item/Item.cpp 
# inventory/inventory.cpp entyties/Entity/Entity.cpp entyties/Oper.cpp 
# game_algorithm/game_algorithm.cpp entyties/Smart.cpp entyties/Wild.cpp entyties/Forager.cpp level/Level.cpp
# tests/test_level.cpp)
# target_link_libraries(test_invent PRIVATE Catch2::Catch2WithMain gcov)
# target_link_libraries(test_entity PRIVATE Catch2::Catch2WithMain gcov)
# target_link_libraries(test_level PRIVATE Catch2::Catch2WithMain gcov)
#target_link_libraries(res ${MY_LIBRARY})
#target_include_directories(res PRIVATE ../3/shared)
#target_include_directories(my_library PUBLIC ../3/shared)