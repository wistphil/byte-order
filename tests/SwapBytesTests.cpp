#include <gtest/gtest.h>

#include "byte_order/SwapBytes.hpp"

#include <array>
#include <limits>
#include <string>

namespace byte_order::tests {

TEST(SwapBytesTests, check_byte_order_swap_bytes_msg)
{
#if defined(BYTE_ORDER_SWAP_BYTES_MSG)
    const std::string msg(BYTE_ORDER_SWAP_BYTES_MSG);
    EXPECT_TRUE(!msg.empty());
#else
    EXPECT_TRUE(false) << "Expected 'BYTE_ORDER_SWAP_BYTES_MSG' to be defined";
#endif
}

TEST(SwapBytesTests, swap_bytes_int16_t)
{
    const std::int16_t val = static_cast<std::int16_t>(0x80FF);
    const std::int16_t swapped = static_cast<std::int16_t>(0xFF80);
    EXPECT_EQ(swapped, detail::swap_bytes_default(val));
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_uint16_t)
{
    const std::uint16_t val = 0xFF99;
    const std::uint16_t swapped = 0x99FF;
    EXPECT_EQ(swapped, detail::swap_bytes_default(val));
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_int32_t)
{
    const std::int32_t val = static_cast<std::int32_t>(0x90AABBCC);
    const std::int32_t swapped = static_cast<std::int32_t>(0xCCBBAA90);
    EXPECT_EQ(swapped, detail::swap_bytes_default(val));
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_uint32_t)
{
    const std::uint32_t val = 0xFFEEDDCC;
    const std::uint32_t swapped = 0xCCDDEEFF;
    EXPECT_EQ(swapped, detail::swap_bytes_default(val));
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_int64_t)
{
    const std::int64_t val = static_cast<std::int64_t>(0x8090FFFF99669966);
    const std::int64_t swapped = static_cast<std::int64_t>(0x66996699FFFF9080);
    EXPECT_EQ(swapped, detail::swap_bytes_default(val));
    EXPECT_EQ(swapped, swap_bytes(val));
}

TEST(SwapBytesTests, swap_bytes_uint64_t)
{
    const std::uint64_t val = 0xFFFF0101FFFF0808;
    const std::uint64_t swapped = 0x0808FFFF0101FFFF;
    EXPECT_EQ(swapped, detail::swap_bytes_default(val));
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
    EXPECT_DOUBLE_EQ(swapped, detail::swap_bytes_default(val));
    EXPECT_DOUBLE_EQ(swapped, swap_bytes(val));
}

} // namespace byte_order::tests
