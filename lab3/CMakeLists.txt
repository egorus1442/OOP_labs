cmake_minimum_required(VERSION 3.10)
project(figures)

set(CMAKE_CXX_STANDARD 14)
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

# Создаем библиотеку из исходных файлов
add_library(figures_lib
    src/triangle.cpp
    src/square.cpp
    src/octagon.cpp
)

# Основной исполняемый файл
add_executable(figures_app src/main.cpp)
target_link_libraries(figures_app figures_lib)

# Тесты
enable_testing()
add_executable(tests tests/figure_tests.cpp)
target_link_libraries(tests
    figures_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
