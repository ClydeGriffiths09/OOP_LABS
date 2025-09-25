cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)
add_library(lab1_library src/eliminate_bits.cpp)

add_executable(main main.cpp)
target_link_libraries(main lab1_library)

enable_testing()

add_executable(lab1_tests tests/tests.cpp)
target_link_libraries(lab1_tests lab1_library gtest_main)
add_test(NAME lab1_tests COMMAND lab1_tests)