cmake_minimum_required(VERSION 3.10)
project(BalagurFate3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)

# Main project sources (common code)
set(LIB_SOURCES
    src/common/globals.cpp
    src/npc/npc.cpp
    src/npc/orc.cpp
    src/npc/knight.cpp
    src/npc/bear.cpp
    src/factory/npc_factory.cpp
    src/visitor/combat_visitor.cpp
    src/observer/console_observer.cpp
    src/observer/file_observer.cpp
    src/game/game.cpp
    src/game/thread_safe_container.cpp
)

# Add coroutine game source
set(COROUTINE_SOURCES
    ${LIB_SOURCES}
    src/game/coroutine_game.cpp
)

# Create libraries for both versions
add_library(game_lib ${LIB_SOURCES})
add_library(coroutine_game_lib ${COROUTINE_SOURCES})

# Set include directories and link threads
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(coroutine_game_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(game_lib PUBLIC Threads::Threads)
target_link_libraries(coroutine_game_lib PUBLIC Threads::Threads)

# Main executables
add_executable(${PROJECT_NAME}_threaded src/main_threaded.cpp)
add_executable(${PROJECT_NAME}_coroutine src/main_coroutine.cpp)

target_link_libraries(${PROJECT_NAME}_threaded PRIVATE game_lib)
target_link_libraries(${PROJECT_NAME}_coroutine PRIVATE coroutine_game_lib)

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