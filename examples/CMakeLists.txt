cmake_minimum_required(VERSION 3.14)
project(byte-order-example LANGUAGES CXX)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    find_package(byte_order REQUIRED)
endif()

add_executable(example
    example.cpp)

target_link_libraries(example
    PRIVATE
        byte_order::byte_order)

