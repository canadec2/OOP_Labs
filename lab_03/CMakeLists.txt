cmake_minimum_required(VERSION 3.10)
project(Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходники
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

set(SOURCES
    ${SRC_DIR}/figure.cpp
    ${SRC_DIR}/hexagon.cpp
    ${SRC_DIR}/octagon.cpp
    ${SRC_DIR}/triangle.cpp
)

add_executable(lab3 main.cpp ${SOURCES})
target_include_directories(lab3 PRIVATE ${SRC_DIR})

# Тесты
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(lab3_tests ${TEST_DIR}/tests.cpp ${SOURCES})
target_include_directories(lab3_tests PRIVATE ${SRC_DIR})
target_link_libraries(lab3_tests GTest::gtest GTest::gtest_main pthread)

enable_testing()
add_test(NAME Lab3Tests COMMAND lab3_tests)