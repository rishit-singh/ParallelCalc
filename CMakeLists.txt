cmake_minimum_required(VERSION 3.0)
project(ParallelCalc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH    
        ${CMAKE_CURRENT_LIST_DIR}/cmake
        ${CMAKE_MODULE_PATH})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include/SDL2 -Wall -D_THREAD_SAFE --std=c++20")

include(FetchContent)

# Fetch dependancy for CppKafka: librdkafka
set(RDKAFKA_BUILD_EXAMPLES OFF ON CACHE INTERNAL "Turn off examples")
set(RDKAFKA_BUILD_TESTS OFF CACHE INTERNAL "Turn off tests")

FetchContent_Declare(
    librdkafka
    GIT_REPOSITORY https://github.com/confluentinc/librdkafka
    GIT_TAG        v2.3.0
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)

# Fetch dependancy: CppKafka
set(CPPKAFKA_DISABLE_EXAMPLES ON CACHE INTERNAL "Turn off examples")
set(CPPKAFKA_DISABLE_TESTS ON CACHE INTERNAL "Turn off tests")

FetchContent_Declare(
    CppKafka
    GIT_REPOSITORY https://github.com/mfontanini/cppkafka.git
    GIT_TAG        v0.3.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# gtest for testing
FetchContent_MakeAvailable(googletest)
#json for json loading
FetchContent_MakeAvailable(json)
#kafka
FetchContent_MakeAvailable(librdkafka)
FetchContent_MakeAvailable(CppKafka)
# GMP for bignum dependencies
find_package(GMP REQUIRED)

file(GLOB ParallelCalc_SOURCES src/*.cpp)
file(GLOB Test_SOURCES tests/*.cpp)
file(GLOB Kafka_SOURCES src/kafka/*.cpp)

# lib for all the calculator sources
add_library(libParallelCalc ${ParallelCalc_SOURCES})
target_include_directories(libParallelCalc PUBLIC include/)
target_link_libraries(libParallelCalc PUBLIC GMP::GMP)

add_library(kafka ${Kafka_SOURCES})
target_include_directories(kafka PUBLIC include/kafka)
target_link_libraries(kafka PUBLIC rdkafka cppkafka nlohmann_json::nlohmann_json)

add_executable(ParallelCalc src/main.cpp)
target_include_directories(ParallelCalc PRIVATE include/)
target_link_libraries(ParallelCalc libParallelCalc rdkafka cppkafka nlohmann_json::nlohmann_json ) 

# build tests

enable_testing()

add_executable(test_basic tests/test_basic.cpp)
target_link_libraries(test_basic GTest::gtest_main libParallelCalc)

add_executable(test_factorial tests/test_factorial.cpp)
target_link_libraries(test_factorial GTest::gtest_main libParallelCalc)

include(GoogleTest)

gtest_discover_tests(test_basic)
