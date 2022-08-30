cmake_minimum_required(VERSION 3.14)
project(byte-order VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

add_library(byte_order INTERFACE)
add_library(byte_order::byte_order ALIAS byte_order)

add_subdirectory(tools)
add_subdirectory(tests)

set(BYTE_ORDER_FILE_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/byte_order)
set(BYTE_ORDER_FILE ${BYTE_ORDER_FILE_PATH}/ByteOrder.hpp)

add_custom_command(
    OUTPUT ${BYTE_ORDER_FILE}
    COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tools/etc ${CMAKE_CURRENT_BINARY_DIR}/tools/etc
    COMMAND cmake -E make_directory ${BYTE_ORDER_FILE_PATH}
    COMMAND generate_byte_order_header > ${BYTE_ORDER_FILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tools
    DEPENDS generate_byte_order_header)

add_custom_target(generated_byte_order_header DEPENDS ${BYTE_ORDER_FILE})
add_dependencies(byte_order generated_byte_order_header)

target_sources(byte_order
    PRIVATE
        ${BYTE_ORDER_FILE}
        include/byte_order/Codec.hpp
        include/byte_order/Codec.inl)

target_include_directories(byte_order
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(CMakePackageConfigHelpers)

    set(package byte_order)

    set(byte_order_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
        CACHE PATH "CMake package config location relative to the install prefix")
    mark_as_advanced(byte_order_INSTALL_CMAKEDIR)

    install(DIRECTORY include/ TYPE INCLUDE)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/ TYPE INCLUDE)

    install(TARGETS byte_order
        EXPORT byte_order-targets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    configure_package_config_file(
        cmake/byte_order-config.cmake.in
        byte_order-config.cmake
        INSTALL_DESTINATION "${byte_order_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(
        "${package}-config-version.cmake"
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/byte_order-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/byte_order-config-version.cmake"
        DESTINATION "${byte_order_INSTALL_CMAKEDIR}")

    install(EXPORT byte_order-targets
        NAMESPACE byte_order::
        DESTINATION ${byte_order_INSTALL_CMAKEDIR})
endif()

