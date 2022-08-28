#include <gtest/gtest.h>

#include "byte_order/Codec.hpp"

namespace byte_order::tests {

TEST(CodecTests, encode_decode_little_int32_t)
{
    std::uint8_t data[sizeof(std::int32_t)] = {};
    const std::int32_t value{125};
    encode_little(data, value);

    auto decoded = decode_little<std::int32_t>(data);

    EXPECT_EQ(value, decoded);
}

TEST(CodecTests, encode_decode_little_uint32_t)
{
    std::uint8_t data[sizeof(std::uint32_t)] = {};
    const std::uint32_t value{125};
    encode_little(data, value);

    auto decoded = decode_little<std::uint32_t>(data);

    EXPECT_EQ(value, decoded);
}

} // namespace byte_order::tests
