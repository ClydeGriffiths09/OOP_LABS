cmake_minimum_required(VERSION 3.10)
project(OOP_LAB_6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main_prog
    main.cpp
    src/npc.cpp
    src/battle_visitor.cpp
    src/observer.cpp
    src/npc_factory.cpp
    src/npc_handle.cpp
    src/dungeon_editor.cpp
)
