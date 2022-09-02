#pragma once

#include "byte_order/ByteOrder.hpp"

#include <cstdint>
#include <type_traits>

namespace byte_order {

template <typename T>
auto swap_bytes(T value) -> std::enable_if_t<std::is_trivially_copyable_v<T>, T>;

inline void encode_little(std::uint8_t * dst, std::int8_t value);
inline void encode_little(std::uint8_t * dst, std::uint8_t value);
inline void encode_little(std::uint8_t * dst, std::int16_t value);
inline void encode_little(std::uint8_t * dst, std::uint16_t value);
inline void encode_little(std::uint8_t * dst, std::int32_t value);
inline void encode_little(std::uint8_t * dst, std::uint32_t value);
inline void encode_little(std::uint8_t * dst, std::int64_t value);
inline void encode_little(std::uint8_t * dst, std::uint64_t value);

inline void encode_big(std::uint8_t * dst, std::int8_t value);
inline void encode_big(std::uint8_t * dst, std::uint8_t value);
inline void encode_big(std::uint8_t * dst, std::int16_t value);
inline void encode_big(std::uint8_t * dst, std::uint16_t value);
inline void encode_big(std::uint8_t * dst, std::int32_t value);
inline void encode_big(std::uint8_t * dst, std::uint32_t value);
inline void encode_big(std::uint8_t * dst, std::int64_t value);
inline void encode_big(std::uint8_t * dst, std::uint64_t value);

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int8_t>, T>;

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint8_t>, T>;

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int16_t>, T>;

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint16_t>, T>;

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>;

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint32_t>, T>;

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int64_t>, T>;

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint64_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int8_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint8_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int16_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint16_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint32_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int64_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint64_t>, T>;

} // namespace byte_order {

#include "Codec.inl"
