project(byte-order-tests LANGUAGES CXX)

find_package(GTest CONFIG REQUIRED)

add_executable(byte_order_tests
    ByteOrderTests.cpp
    CodecTests.cpp
    SwapBytesTests.cpp)

add_dependencies(byte_order_tests generated_byte_order_header)

target_link_libraries(byte_order_tests
    PRIVATE
        byte_order::byte_order
        GTest::gtest
        GTest::gtest_main)

add_test(NAME byte_order_tests COMMAND byte_order_tests)

