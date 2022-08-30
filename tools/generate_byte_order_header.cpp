#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>

auto detect_byte_order() -> std::string
{
    constexpr std::int32_t little{1};
    constexpr std::int32_t big{2};

    const std::int32_t val{0x02000001};
    const std::int32_t native = reinterpret_cast<const char *>(&val)[0];

    switch(native) {
        case little:
            return "little";
        case big:
            return "big";
        default:
            break;
    }

    return "unsupported";
}

auto main() -> int
{
    const std::string file{"./etc/ByteOrder.hpp.in"};
    std::ifstream fin(file);
    if (!fin) {
        return -1;
    }

    const std::string byte_order_header(
            std::istreambuf_iterator<char>{fin},
            std::istreambuf_iterator<char>{});

    auto byte_order = detect_byte_order();
    std::printf(byte_order_header.c_str(), byte_order.c_str());

    return 0;
}
