cmake_minimum_required(VERSION 3.10)
project(BalagurFate3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main project sources (без main.cpp)
set(LIB_SOURCES
    src/npc/npc.cpp
    src/npc/orc.cpp
    src/npc/knight.cpp
    src/npc/bear.cpp
    src/factory/npc_factory.cpp
    src/visitor/combat_visitor.cpp
    src/observer/console_observer.cpp
    src/observer/file_observer.cpp
    src/game/game.cpp
)

# Создаем библиотеку из общего кода
add_library(game_lib ${LIB_SOURCES})
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE game_lib)

# Tests setup
enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

# Test sources
set(TEST_SOURCES
    tests/npc_test.cpp
    tests/combat_test.cpp
    tests/factory_test.cpp
)

# Test executable
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE 
    game_lib
    gtest 
    gtest_main
)