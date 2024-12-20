cmake_minimum_required(VERSION 3.10)
project(Lab6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем директорию с исходниками в пути для поиска заголовков
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
    ${SRC_DIR}/npc.cpp
    ${SRC_DIR}/bear.cpp
    ${SRC_DIR}/vup.cpp
    ${SRC_DIR}/vykhukhol.cpp
    ${SRC_DIR}/factory.cpp
    ${SRC_DIR}/visitor.cpp
)

add_executable(lab6 main.cpp ${SOURCES})

# Тесты
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Lab6Tests tests/tests.cpp ${SOURCES})
target_link_libraries(Lab6Tests GTest::gtest GTest::gtest_main pthread)

enable_testing()
add_test(NAME Lab6Tests COMMAND Lab6Tests)