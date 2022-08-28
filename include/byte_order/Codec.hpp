#pragma once

#include "byte_order/ByteOrder.hpp"

#include <cstdint>
#include <type_traits>

namespace byte_order {

inline void encode_little(std::uint8_t * dst, std::int32_t value);
inline void encode_little(std::uint8_t * dst, std::uint32_t value);

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>;

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::uint32_t>, T>;

} // namespace byte_order {

#include "Codec.inl"
