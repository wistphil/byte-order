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
Sample output:
```
Byte Order is little
encoded 0x1a2b3c4d in little endian: 0x4d3c2b1a
decoded little endian value 1a2b3c4d
```
## Build using CMake
Clone and initialize the build directory
```
$ git clone https://github.com/wistphil/byte-order.git
$ cd byte-order/
$ mkdir build
```
Initialize CMake using 'preset' (currently only 'linux' is supported).
```
$ cmake --preset linux --install-prefix <path to install directory>
```
Note that `--install-prefix` is only needed if building this project stand-alone and plan on importing the project with `FindPackage()`. It is not necessary if consuming this library as a sub project (with FetchContent).
Build
```
$ cmake --build build/
```
Install
```
$ cmake --install build/
```
### Importing with FindPackage
In the project that depends on byte-order, include the directory to where byte-order is installed in the `CMAKE_PREFIX_PATH`. For example,
```
$ cmake Ninja -DCMAKE_PREFIX_PATH=<path to where byte-order is installed> -DCMAKE_CXX_STANDARD=17 -S . -B build/
```
Use `FindPackage()` in your CMakeLists.txt
```
find_package(byte_order REQUIRED)

...

target_link_libraries(my_proj
    PRIVATE
        byte_order::byte_order)
```
