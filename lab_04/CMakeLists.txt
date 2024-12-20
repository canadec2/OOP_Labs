cmake_minimum_required(VERSION 3.10)
project(lab_04)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Include directories
include_directories(include)

# Add library
add_library(lab04_lib src/main.cpp)

# Add executable for main
add_executable(lab04_exe src/main.cpp)
target_link_libraries(lab04_exe lab04_lib)

# Add executable for tests
add_executable(lab04_tests tests/tests.cpp)
target_link_libraries(lab04_tests lab04_lib gtest_main)

add_test(NAME lab04_tests COMMAND lab04_tests)
