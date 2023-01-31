#include "byte_order/ByteOrder.hpp"
#include "byte_order/Codec.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

auto main() -> int
{
    if constexpr (byte_order::ByteOrder::native == byte_order::ByteOrder::little) {
        std::cout << "Byte Order is little\n";
    }
    else {
        std::cout << "Byte Order is big\n";
    }

    const int value{0x1a2b3c4d};
    std::vector<uint8_t> buffer(sizeof(value));

    byte_order::encode_little(buffer.data(), value);

    std::cout << "encoded 0x" << std::hex << value << " in little endian: 0x";
    std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<int>(std::cout));

    const auto decoded_value = byte_order::decode_little<int>(buffer.data());
    std::cout << "\ndecoded little endian value " << decoded_value << '\n';

    return 0;
}
