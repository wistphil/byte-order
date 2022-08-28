#include <cstdint>
#include <cstdio>
#include <string>

const std::string byte_order_header = R"(
#pragma once

namespace byte_order {
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# define BYTE_ORDER_NATIVE_BYTE_ORDER little
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
# define BYTE_ORDER_NATIVE_BYTE_ORDER big
#elif defined(__LITTLE_ENDIAN__)
# define BYTE_ORDER_NATIVE_BYTE_ORDER little
#elif defined(__BIG_ENDIAN__)
# define BYTE_ORDER_NATIVE_BYTE_ORDER big
#elif defined(_MSC_VER) || defined(__i386__) || defined(__x86_64__)
# define BYTE_ORDER_NATIVE_BYTE_ORDER little
#else
#define DETECTED_NATIVE_BYTE_ORDER %s
#if !defined(BYTE_ORDER_NATIVE_BYTE_ORDER)
#define BYTE_ORDER_NATIVE_BYTE_ORDER DETECTED_NATIVE_BYTE_ORDER
#endif
#endif

enum class ByteOrder
{
    little,
    big,
    native = BYTE_ORDER_NATIVE_BYTE_ORDER
};
} // namespace byte_order {

#undef DETECTED_NATIVE_BYTE_ORDER
#undef BYTE_ORDER_NATIVE_BYTE_ORDER
)";

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
    auto byte_order = detect_byte_order();
    std::printf(byte_order_header.c_str(), byte_order.c_str());

    return 0;
}
