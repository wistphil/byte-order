#pragma once

#include <cstring>

namespace byte_order {

namespace detail {

template <typename T>
auto swap_bytes_default(T value) ->
        std::enable_if_t<std::has_unique_object_representations_v<T> || (std::is_same_v<double, T> && std::numeric_limits<double>::is_iec559), T>
{
    std::uint8_t input_buf[sizeof(value)];
    std::memcpy(input_buf, &value, sizeof(value));

    std::uint8_t output_buf[sizeof(value)];
    std::size_t left{0};
    for (std::size_t right{sizeof(value)}; right > 0; --right) {
        output_buf[left++] = input_buf[right - 1];
    }

    T result{};
    std::memcpy(&result, output_buf, sizeof(value));

    return result;
}

inline auto swap_bytes_default(std::int16_t value) -> std::int16_t
{
    return static_cast<std::int16_t>(swap_bytes_default(static_cast<std::uint16_t>(value)));
}

inline auto swap_bytes_default(std::uint16_t value) -> std::uint16_t
{
    const std::uint16_t b0 = static_cast<std::uint16_t>(value >> 8);
    const std::uint16_t b1 = static_cast<std::uint16_t>(value << 8);
    return b1 | b0;
}

inline auto swap_bytes_default(std::int32_t value) -> std::int32_t
{
    return static_cast<std::int32_t>(swap_bytes_default(static_cast<std::uint32_t>(value)));
}

inline auto swap_bytes_default(std::uint32_t value) -> std::uint32_t
{
    const std::uint32_t b0 = static_cast<std::uint32_t>(value >> 24);
    const std::uint32_t b1 = static_cast<std::uint32_t>((value >> 8) & 0x0000FF00);
    const std::uint32_t b2 = static_cast<std::uint32_t>((value << 8) & 0x00FF0000);
    const std::uint32_t b3 = static_cast<std::uint32_t>((value << 24) & 0xFF000000);
    return b3 | b2 | b1 | b0;
}

inline auto swap_bytes_default(std::int64_t value) -> std::int64_t
{
    return static_cast<std::int64_t>(swap_bytes_default(static_cast<std::uint64_t>(value)));
}

inline auto swap_bytes_default(std::uint64_t value) -> std::uint64_t
{
    const std::uint64_t b0 = static_cast<std::uint64_t>(value >> 56);
    const std::uint64_t b1 = static_cast<std::uint64_t>((value >> 40) & 0x000000000000FF00);
    const std::uint64_t b2 = static_cast<std::uint64_t>((value >> 24) & 0x0000000000FF0000);
    const std::uint64_t b3 = static_cast<std::uint64_t>((value >> 8) & 0x00000000FF000000);
    const std::uint64_t b4 = static_cast<std::uint64_t>((value << 8) & 0x000000FF00000000);
    const std::uint64_t b5 = static_cast<std::uint64_t>((value << 24) & 0x0000FF0000000000);
    const std::uint64_t b6 = static_cast<std::uint64_t>((value << 40) & 0x00FF000000000000);
    const std::uint64_t b7 = static_cast<std::uint64_t>((value << 56) & 0xFF00000000000000);
    return b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0;
}

} // namespace detail {

template <typename T>
auto swap_bytes(T value) -> std::enable_if_t<std::has_unique_object_representations_v<T>, T>
{
    return detail::swap_bytes_default(value);
}

#if (defined(__clang__) && __has_builtin(__builtin_bswap16))

auto swap_bytes(std::int16_t value) -> std::int16_t
{
    return static_cast<std::int16_t>(__builtin_bswap16(static_cast<std::uint16_t>(value)));
}

auto swap_bytes(std::uint16_t value) -> std::uint16_t
{
    return __builtin_bswap16(value);
}

#else

auto swap_bytes(std::int16_t value) -> std::int16_t
{
    return detail::swap_bytes_default(value);
}

auto swap_bytes(std::uint16_t value) -> std::uint16_t
{
    return detail::swap_bytes_default(value);
}

#endif

#if (defined(__clang__) && __has_builtin(__builtin_bswap32))

auto swap_bytes(std::int32_t value) -> std::int32_t
{
    return static_cast<std::int32_t>(__builtin_bswap32(static_cast<std::uint32_t>(value)));
}

auto swap_bytes(std::uint32_t value) -> std::uint32_t
{
    return __builtin_bswap32(value);
}

#else

auto swap_bytes(std::int32_t value) -> std::int32_t
{
    return detail::swap_bytes_default(value);
}

auto swap_bytes(std::uint32_t value) -> std::uint32_t
{
    return detail::swap_bytes_default(value);
}

#endif

#if (defined(__clang__) && __has_builtin(__builtin_bswap64))

auto swap_bytes(std::int64_t value) -> std::int64_t
{
    return static_cast<std::int64_t>(__builtin_bswap64(static_cast<std::uint64_t>(value)));
}

auto swap_bytes(std::uint64_t value) -> std::uint64_t
{
    return __builtin_bswap64(value);
}

#else

auto swap_bytes(std::int64_t value) -> std::int64_t
{
    return detail::swap_bytes_default(value);
}

auto swap_bytes(std::uint64_t value) -> std::uint64_t
{
    return detail::swap_bytes_default(value);
}

#endif

auto swap_bytes(double value) -> std::enable_if_t<std::numeric_limits<double>::is_iec559, double>
{
    return detail::swap_bytes_default(value);
}

} // namespace byte_order {
