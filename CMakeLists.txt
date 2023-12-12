cmake_minimum_required(VERSION 3.0)
project(ParallelCalc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include/SDL2 -Wall -D_THREAD_SAFE --std=c++20")

file(GLOB ParallelCalc_SOURCES src/*.cpp)

add_library(libParallelCalc ${ParallelCalc_SOURCES} src/calculator.cpp)
target_include_directories(libParallelCalc PUBLIC include/)

add_executable(ParallelCalc src/main.cpp)
target_include_directories(ParallelCalc PRIVATE include/)
target_link_libraries(ParallelCalc libParallelCalc) 
 