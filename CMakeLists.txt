cmake_minimum_required(VERSION 3.10)

# THIS SECTION PROBABLY NOT NEEDED
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

set(PROJECT_NAME matrix)
project(${PROJECT_NAME})

set(MTRX_LIBRARY "${PROJECT_NAME}")
set(MTRX_TESTS   "test_${PROJECT_NAME}")
set(MTRX_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("${PROJECT_NAME}" gtest)

# BUILD
add_subdirectory(gtest)
add_subdirectory(test)