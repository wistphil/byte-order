cmake_minimum_required(VERSION 3.14)
project(byte-order LANGUAGES CXX)

add_subdirectory(tools)
add_subdirectory(tests)

set(BYTE_ORDER_FILE_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/byte_order)
set(BYTE_ORDER_FILE ${BYTE_ORDER_FILE_PATH}/ByteOrder.hpp)

add_custom_target(generated_byte_order_header DEPENDS ${BYTE_ORDER_FILE})

add_custom_command(
        OUTPUT ${BYTE_ORDER_FILE}
        COMMAND cmake -E make_directory ${BYTE_ORDER_FILE_PATH}
        COMMAND generate_byte_order_header > ${BYTE_ORDER_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tools
        DEPENDS generate_byte_order_header)

add_library(byte_order INTERFACE)
add_library(byte_order::byte_order ALIAS byte_order)
add_dependencies(byte_order generated_byte_order_header)

target_include_directories(byte_order
        INTERFACE 
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

