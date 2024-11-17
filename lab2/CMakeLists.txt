cmake_minimum_required(VERSION 3.14)
project(thirteen_project)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление основной библиотеки
add_library(thirteen_lib
    src/thirteen.cpp
)

target_include_directories(thirteen_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Настройка Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Добавление тестов
enable_testing()
add_executable(thirteen_tests
    tests/thirteen_tests.cpp
)

target_link_libraries(thirteen_tests
    thirteen_lib
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(thirteen_tests) 