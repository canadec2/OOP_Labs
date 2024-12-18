# Лабораторная работа 1
add_library(lab01_lib src/solution.cpp)
target_include_directories(lab01_lib PUBLIC include)

add_executable(lab01_exe main.cpp)
target_link_libraries(lab01_exe PRIVATE lab01_lib)

# Добавление тестов
add_executable(tests01 test/tests01.cpp)
target_link_libraries(tests01 PRIVATE lab01_lib gtest_main)

add_test(NAME Lab01Tests COMMAND tests01)
