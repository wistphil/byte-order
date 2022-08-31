#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
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

auto load_file(std::filesystem::path file) -> std::string
{
    std::ifstream fin(file);
    if (!fin) {
        return {};
    }
    return std::string(
            std::istreambuf_iterator<char>{fin},
            std::istreambuf_iterator<char>{});
}

auto main() -> int
{
    const std::filesystem::path file("./etc/ByteOrder.hpp.in");
    const auto byte_order_header = load_file(file);
    if (byte_order_header.empty()) {
        return -1;
    }

    const auto byte_order = detect_byte_order();

    std::cout << std::regex_replace(
            byte_order_header,
            std::regex("@DETECTED_BYTE_ORDER@"),
            byte_order);

    return 0;
}
