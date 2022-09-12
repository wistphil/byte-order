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
