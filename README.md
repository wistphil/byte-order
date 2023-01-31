# byte-order
`byte-order` is a C++ library for encoding and decoding integral types to and from little and big endian. It provides an enumeration, `ByteOrder`, for checking the byte order of the platform, which can be either `little` or `big`, and a set of encode and decode free frunctions.

The `ByteOrder` enumeration is defined as:
```cpp
enum class ByteOrder
{
    little,
    big,
    native = // either 'little' or 'big', depending on the platform
};
```
The encode/decode function signatures are defined as:
(only `std::int32_t` is shown for brevity)
```cpp
inline void encode_little(std::uint8_t * dst, std::int32_t value);
inline void encode_big(std::uint8_t * dst, std::int32_t value);

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>;
```
Example
```cpp
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
```
