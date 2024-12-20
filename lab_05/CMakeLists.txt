cmake_minimum_required(VERSION 3.10)

project(lab_05)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Создаём статическую библиотеку из solution.cpp
add_library(lab5_lib src/solution.cpp)

# Основной исполняемый файл
add_executable(lab5_main main.cpp)
target_link_libraries(lab5_main PRIVATE lab5_lib)

enable_testing()

# Тесты
add_executable(lab5_tests tests/tests05.cpp)
target_link_libraries(lab5_tests PRIVATE lab5_lib gtest_main)

# Регистрируем тесты
add_test(NAME Lab5Tests COMMAND lab5_tests)