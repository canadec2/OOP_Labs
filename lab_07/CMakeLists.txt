cmake_minimum_required(VERSION 3.10)
project(Lab7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# Основные исходные файлы
set(SOURCES
    ${SRC_DIR}/bear.cpp
    ${SRC_DIR}/vup.cpp
    ${SRC_DIR}/vykhukhol.cpp
    ${SRC_DIR}/npc.cpp
    ${SRC_DIR}/factory.cpp
    ${SRC_DIR}/observers.cpp
    ${SRC_DIR}/visitor.cpp
)

# Основная программа
add_executable(lab7 main.cpp ${SOURCES})
target_include_directories(lab7 PRIVATE ${SRC_DIR})

# Тесты
# Подключение GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCES
    ${TEST_DIR}/tests.cpp
)

add_executable(Lab7Tests ${TEST_SOURCES} ${SOURCES})
target_include_directories(Lab7Tests PRIVATE ${SRC_DIR})
target_link_libraries(Lab7Tests GTest::gtest GTest::gtest_main pthread)

enable_testing()
add_test(NAME Lab7Tests COMMAND Lab7Tests)
