#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace byte_order {

inline void encode_little(std::uint8_t * dst, std::int8_t value);
inline void encode_little(std::uint8_t * dst, std::uint8_t value);
inline void encode_little(std::uint8_t * dst, std::int16_t value);
inline void encode_little(std::uint8_t * dst, std::uint16_t value);
inline void encode_little(std::uint8_t * dst, std::int32_t value);
inline void encode_little(std::uint8_t * dst, std::uint32_t value);
inline void encode_little(std::uint8_t * dst, std::int64_t value);
inline void encode_little(std::uint8_t * dst, std::uint64_t value);
inline auto encode_little(std::uint8_t * dst, double value) -> std::enable_if_t<std::numeric_limits<double>::is_iec559, void>;

inline void encode_big(std::uint8_t * dst, std::int8_t value);
inline void encode_big(std::uint8_t * dst, std::uint8_t value);
inline void encode_big(std::uint8_t * dst, std::int16_t value);
inline void encode_big(std::uint8_t * dst, std::uint16_t value);
inline void encode_big(std::uint8_t * dst, std::int32_t value);
inline void encode_big(std::uint8_t * dst, std::uint32_t value);
inline void encode_big(std::uint8_t * dst, std::int64_t value);
inline void encode_big(std::uint8_t * dst, std::uint64_t value);
inline auto encode_big(std::uint8_t * dst, double value) -> std::enable_if_t<std::numeric_limits<double>::is_iec559, void>;

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
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, double>, T>;

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

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, double>, T>;

} // namespace byte_order {

#include "byte_order/Codec.inl"
