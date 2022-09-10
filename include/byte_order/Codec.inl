#pragma once

#include <cstring>

namespace byte_order {

namespace detail {

struct ByteOrderLittle : std::integral_constant<ByteOrder, ByteOrder::little> {};
struct ByteOrderBig : std::integral_constant<ByteOrder, ByteOrder::big> {};
struct ByteOrderNative : std::integral_constant<ByteOrder, ByteOrder::native> {};

template <typename T, typename... Ts>
struct IsOneOfImpl;

template <typename T, typename U, typename... Ts>
struct IsOneOfImpl<T, U, Ts...>
{
    static constexpr bool value = IsOneOfImpl<T, Ts...>::value;
};

template <typename T, typename... Ts>
struct IsOneOfImpl<T, T, Ts...>
{
    static constexpr bool value = true;
};

template <typename T>
struct IsOneOfImpl<T>
{
    static constexpr bool value = false;
};

template <typename T, typename... Ts>
struct IsOneOf
{
    static constexpr bool value = IsOneOfImpl<T, Ts...>::value;
};

template <typename T>
struct IsByteOrderT
{
    static constexpr bool value = IsOneOf<T, ByteOrderLittle, ByteOrderBig>::value;
};

template <typename T>
struct IsInteger
{
    static constexpr bool value = IsOneOf<T, std::uint8_t, std::int8_t, std::uint16_t, std::int16_t, std::uint32_t, std::int32_t, std::uint64_t, std::int64_t>::value;
};

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

template <typename T, typename = std::enable_if_t<IsInteger<T>::value>, typename ByteOrderT, typename = std::enable_if_t<IsByteOrderT<ByteOrderT>::value>>
void encode(std::uint8_t * dst, T value, ByteOrderT target_byte_order)
{
    if constexpr (target_byte_order == ByteOrderNative::value) {
        std::memcpy(dst, &value, sizeof(value));
    }
    else {
        auto swapped = swap_bytes(value);
        std::memcpy(dst, &swapped, sizeof(swapped));
    }
}

template <typename T, typename ByteOrderT, typename = std::enable_if_t<IsByteOrderT<ByteOrderT>::value>>
auto decode(std::uint8_t * src, ByteOrderT target_byte_order) -> std::enable_if_t<IsInteger<T>::value, T>
{
    T  result{};
    if constexpr (target_byte_order == ByteOrderNative::value) {
        std::memcpy(&result, src, sizeof(result));
    }
    else {
        T tmp{};
        std::memcpy(&tmp, src, sizeof(tmp));
        result = swap_bytes(tmp);
    }
    return result;
}

} // namespace detail

template <typename T>
auto swap_bytes(T value) -> std::enable_if_t<std::has_unique_object_representations_v<T>, T>
{
    return detail::swap_bytes_impl(value);
}

template <typename T>
auto swap_bytes(T value) -> std::enable_if_t<std::is_same_v<double, T> && std::numeric_limits<double>::is_iec559, T>
{
    return detail::swap_bytes_impl(value);
}

void encode_little(std::uint8_t * dst, std::int8_t value)
{
    detail::encode(dst, value, detail::ByteOrderLittle{});
}

void encode_little(std::uint8_t * dst, std::uint8_t value)
{
    detail::encode(dst, value, detail::ByteOrderLittle{});
}

void encode_little(std::uint8_t * dst, std::int16_t value)
{
    detail::encode(dst, value, detail::ByteOrderLittle{});
}

void encode_little(std::uint8_t * dst, std::uint16_t value)
{
    detail::encode(dst, value, detail::ByteOrderLittle{});
}

void encode_little(std::uint8_t * dst, std::int32_t value)
{
    detail::encode(dst, value, detail::ByteOrderLittle{});
}

void encode_little(std::uint8_t * dst, std::uint32_t value)
{
    detail::encode(dst, value, detail::ByteOrderLittle{});
}

void encode_little(std::uint8_t * dst, std::int64_t value)
{
    detail::encode(dst, value, detail::ByteOrderLittle{});
}

void encode_little(std::uint8_t * dst, std::uint64_t value)
{
    detail::encode(dst, value, detail::ByteOrderLittle{});
}

void encode_big(std::uint8_t * dst, std::int8_t value)
{
    detail::encode(dst, value, detail::ByteOrderBig{});
}

void encode_big(std::uint8_t * dst, std::uint8_t value)
{
    detail::encode(dst, value, detail::ByteOrderBig{});
}

void encode_big(std::uint8_t * dst, std::int16_t value)
{
    detail::encode(dst, value, detail::ByteOrderBig{});
}

void encode_big(std::uint8_t * dst, std::uint16_t value)
{
    detail::encode(dst, value, detail::ByteOrderBig{});
}

void encode_big(std::uint8_t * dst, std::int32_t value)
{
    detail::encode(dst, value, detail::ByteOrderBig{});
}

void encode_big(std::uint8_t * dst, std::uint32_t value)
{
    detail::encode(dst, value, detail::ByteOrderBig{});
}

void encode_big(std::uint8_t * dst, std::int64_t value)
{
    detail::encode(dst, value, detail::ByteOrderBig{});
}

void encode_big(std::uint8_t * dst, std::uint64_t value)
{
    detail::encode(dst, value, detail::ByteOrderBig{});
}

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int8_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderLittle{});
}

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint8_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderLittle{});
}

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int16_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderLittle{});
}

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint16_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderLittle{});
}

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderLittle{});
}

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint32_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderLittle{});
}

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int64_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderLittle{});
}

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint64_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderLittle{});
}

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int8_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderBig{});
}

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint8_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderBig{});
}

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int16_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderBig{});
}

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint16_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderBig{});
}

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderBig{});
}

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint32_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderBig{});
}

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int64_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderBig{});
}

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint64_t>, T>
{
    return detail::decode<T>(src, detail::ByteOrderBig{});
}

} // namespace byte_order {
