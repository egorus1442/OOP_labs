cmake_minimum_required(VERSION 3.10)
project(dynamic_array)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Добавляем директорию с заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR}/include)

# Создаем библиотеку
add_library(dynamic_array_lib
    src/dynamic_array.cpp
    src/dynamic_memory_resource.cpp
)

# Тесты
enable_testing()
add_executable(tests tests/dynamic_array_tests.cpp)
target_link_libraries(tests 
    GTest::gtest_main
    dynamic_array_lib
)

# Основной исполняемый файл
add_executable(dynamic_array_app src/main.cpp)
target_link_libraries(dynamic_array_app dynamic_array_lib)

include(GoogleTest)
gtest_discover_tests(tests)