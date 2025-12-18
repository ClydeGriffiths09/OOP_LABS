cmake_minimum_required(VERSION 3.10)
project(OOP_LAB_6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

set(SRC_FILES
    src/battle_visitor.cpp
    src/dungeon_editor.cpp
    src/npc_factory.cpp
    src/npc_handle.cpp
    src/npc.cpp
    src/observer.cpp
    src/simulation.cpp
)

set(HEADER_FILES
    include/battle_visitor.hpp
    include/dungeon_editor.hpp
    include/npc_factory.hpp
    include/npc_handle.hpp
    include/npc.hpp
    include/observer.hpp
)

add_executable(main_prog
    main.cpp
    ${SRC_FILES}
)

add_library(game_lib ${SRC_FILES} ${HEADER_FILES})
target_include_directories(game_lib PUBLIC include)

add_executable(lab_tests
    tests/tests.cpp
    ${SRC_FILES}
)

target_link_libraries(lab_tests 
    PRIVATE 
    gtest 
    gtest_main
)

target_link_libraries(main_prog game_lib)

enable_testing()
add_test(NAME run_tests COMMAND lab_tests)