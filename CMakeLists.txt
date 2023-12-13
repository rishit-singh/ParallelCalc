cmake_minimum_required(VERSION 3.0)
project(ParallelCalc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH    
        ${CMAKE_CURRENT_LIST_DIR}/cmake
        ${CMAKE_MODULE_PATH})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include/SDL2 -Wall -D_THREAD_SAFE --std=c++20")

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# gtest for testing
FetchContent_MakeAvailable(googletest)

# GMP for bignum dependencies
find_package(GMP REQUIRED)
 
file(GLOB ParallelCalc_SOURCES src/*.cpp)
file(GLOB Test_SOURCES tests/*.cpp)

# lib for all the calculator sources
add_library(libParallelCalc ${ParallelCalc_SOURCES} src/calculator.cpp)
target_include_directories(libParallelCalc PUBLIC include/)
target_link_libraries(libParallelCalc PUBLIC GMP::GMP)

add_executable(ParallelCalc src/main.cpp)
target_include_directories(ParallelCalc PRIVATE include/)
target_link_libraries(ParallelCalc libParallelCalc) 

# build tests

enable_testing()

add_executable(test_basic tests/test_basic.cpp)
target_link_libraries(test_basic GTest::gtest_main libParallelCalc)

include(GoogleTest)

gtest_discover_tests(test_basic)
