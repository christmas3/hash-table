cmake_minimum_required(VERSION 3.14)
project(hash_table)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

add_executable(${PROJECT_NAME} main.cpp HashTable.h HashTableTest.cpp)

target_link_libraries(${PROJECT_NAME} gtest_main gtest pthread)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
