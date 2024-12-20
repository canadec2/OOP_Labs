cmake_minimum_required(VERSION 3.10)

project(lab_01)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Добавляем библиотеку для решения
add_library(lab1_lib src/solution.cpp)

# Включаем директорию с заголовочными файлами
target_include_directories(lab1_lib PUBLIC include)

# Создание основного исполняемого файла
add_executable(lab1_main main.cpp)

# Линковка библиотеки с исполняемым файлом
target_link_libraries(lab1_main PRIVATE lab1_lib)

# Включаем поддержку тестов
enable_testing()

# Создание тестов
add_executable(lab1_tests test/tests01.cpp)

# Линковка тестов с библиотекой и Google Test
target_link_libraries(lab1_tests PRIVATE lab1_lib gtest_main)

# Добавление тестов в набор тестирования
add_test(NAME Lab1Tests COMMAND lab1_tests)