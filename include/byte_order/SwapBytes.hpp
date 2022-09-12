#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace byte_order {

template <typename T>
auto swap_bytes(T value) -> std::enable_if_t<std::has_unique_object_representations_v<T>, T>;

inline auto swap_bytes(std::int16_t value) -> std::int16_t;
inline auto swap_bytes(std::uint16_t value) -> std::uint16_t;
inline auto swap_bytes(std::int32_t value) -> std::int32_t;
inline auto swap_bytes(std::uint32_t value) -> std::uint32_t;
inline auto swap_bytes(std::int64_t value) -> std::int64_t;
inline auto swap_bytes(std::uint64_t value) -> std::uint64_t;
inline auto swap_bytes(double value) -> std::enable_if_t<std::numeric_limits<double>::is_iec559, double>;

} // namespace byte_order {

#include "byte_order/SwapBytes.inl"
