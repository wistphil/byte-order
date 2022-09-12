#pragma once

#include <cstring>

namespace byte_order {

namespace detail {

template <typename T>
auto swap_bytes_impl(T value) ->
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

} // namespace detail {

template <typename T>
auto swap_bytes(T value) -> std::enable_if_t<std::has_unique_object_representations_v<T>, T>
{
    return detail::swap_bytes_impl(value);
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
    return detail::swap_bytes_impl(value);
}

auto swap_bytes(std::uint16_t value) -> std::uint16_t
{
    return detail::swap_bytes_impl(value);
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
    return detail::swap_bytes_impl(value);
}

auto swap_bytes(std::uint32_t value) -> std::uint32_t
{
    return detail::swap_bytes_impl(value);
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
    return detail::swap_bytes_impl(value);
}

auto swap_bytes(std::uint64_t value) -> std::uint64_t
{
    return detail::swap_bytes_impl(value);
}

#endif

auto swap_bytes(double value) -> std::enable_if_t<std::numeric_limits<double>::is_iec559, double>
{
    return detail::swap_bytes_impl(value);
}

} // namespace byte_order {
