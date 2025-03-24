cmake_minimum_required(VERSION 3.10)
project(Lab2)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем статическую библиотеку для класса Detail
add_library(DetailLib STATIC src/Detail.cpp)

# Добавляем статическую библиотеку для класса AssemblyInstruction
add_library(AssemblyInstructionLib STATIC src/AssemblyInstruction.cpp)

# Добавляем исполняемый файл для основной программы
add_executable(Lab2App src/main.cpp src/DialogFunctions.cpp src/pricladnay.cpp)

# Подключаем библиотеки к исполняемому файлу
target_link_libraries(Lab2App DetailLib AssemblyInstructionLib)
#target_link_libraries(Lab2App DetailLib)
