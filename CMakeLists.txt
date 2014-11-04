cmake_minimum_required(VERSION 2.8)
project(codedive)

add_subdirectory(gtest-1.6.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "-std=c++11 -Os -Wall -Wextra -Wfatal-errors -save-temps")

add_executable(rt main.cpp pi-runtime.cpp)
set_target_properties(rt PROPERTIES COMPILE_FLAGS "-std=c++11")
target_link_libraries(rt gtest gtest_main)

add_executable(cpp03 main.cpp pi-c++03.cpp)
set_target_properties(cpp03 PROPERTIES COMPILE_FLAGS "-std=c++03")
target_link_libraries(cpp03 gtest gtest_main)

add_executable(cpp11 main.cpp pi-c++11.cpp)
set_target_properties(cpp11 PROPERTIES COMPILE_FLAGS "-std=c++11")
target_link_libraries(cpp11 gtest gtest_main)

add_executable(cpp14 main.cpp pi-c++14.cpp)
set_target_properties(cpp14 PROPERTIES COMPILE_FLAGS "-std=c++1y")
target_link_libraries(cpp14 gtest gtest_main)
