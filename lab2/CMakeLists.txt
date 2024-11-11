cmake_minimum_required(VERSION 3.10)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)

# Указываем путь к Google Test
set(GTEST_ROOT "/usr/local/Cellar/googletest/1.15.2")
include_directories(${GTEST_ROOT}/include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_lab2 tests/test_lab2.cpp)
target_link_libraries(test_lab2 ${GTEST_LIBRARIES} pthread)
