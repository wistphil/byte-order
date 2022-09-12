#include <gtest/gtest.h>

#include "byte_order/SwapBytes.hpp"

#include <array>
#include <limits>

namespace byte_order::tests {

TEST(SwapBytesTests, swap_bytes_int16_t)
{
    const std::int16_t val = 0x1122;
    const std::int16_t swapped = 0x2211;
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_uint16_t)
{
    const std::uint16_t val = 0x1122;
    const std::uint16_t swapped = 0x2211;
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_int32_t)
{
    const std::int32_t val = 0x11223344;
    const std::int32_t swapped = 0x44332211;
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_uint32_t)
{
    const std::uint32_t val = 0x11223344;
    const std::uint32_t swapped = 0x44332211;
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_int64_t)
{
    const std::int64_t val = 0x1111111122222222;
    const std::int64_t swapped = 0x2222222211111111;
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_uint64_t)
{
    const std::uint64_t val = 0x1111111122222222;
    const std::uint64_t swapped = 0x2222222211111111;
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_double)
{
    if constexpr (!std::numeric_limits<double>::is_iec559) {
        return;
    }

    const double val = 1234567.1234567;
    std::array<std::uint8_t, sizeof(val)> array{};
    std::memcpy(&array[0], &val, sizeof(val));
    std::reverse(array.begin(), array.end());
    double swapped{0};
    std::memcpy(&swapped, &array[0], sizeof(swapped));
    EXPECT_DOUBLE_EQ(swapped, swap_bytes(val));
}

} // namespace byte_order::tests
