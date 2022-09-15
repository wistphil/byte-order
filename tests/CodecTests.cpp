#include <gtest/gtest.h>

#include "byte_order/Codec.hpp"

#include <array>
#include <limits>

namespace byte_order::tests {

namespace {

template <typename T>
T encode_decode_little(T val)
{
    std::uint8_t data[sizeof(T)] = {};
    encode_little(data, val);
    return decode_little<T>(data);
}

template <typename T>
T encode_decode_big(T val)
{
    std::uint8_t data[sizeof(T)] = {};
    encode_big(data, val);
    return decode_big<T>(data);
}

} // anonymous namespace

TEST(CodecTests, encode_decode_little_int8_t)
{
    std::int8_t val{std::numeric_limits<std::int8_t>::min()};
    std::int8_t decoded = encode_decode_little(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_little_uint8_t)
{
    std::uint8_t val{std::numeric_limits<std::uint8_t>::max()};
    std::uint8_t decoded = encode_decode_little(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_little_int16_t)
{
    std::int16_t val{std::numeric_limits<std::int16_t>::min()};
    std::int16_t decoded = encode_decode_little(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_little_uint16_t)
{
    std::uint16_t val{std::numeric_limits<std::uint16_t>::max()};
    std::uint16_t decoded = encode_decode_little(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_little_int32_t)
{
    std::int32_t val{std::numeric_limits<std::int32_t>::min()};
    std::int32_t decoded = encode_decode_little(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_little_uint32_t)
{
    std::uint32_t val{std::numeric_limits<std::uint32_t>::max()};
    std::uint32_t decoded = encode_decode_little(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_little_int64_t)
{
    std::int64_t val{std::numeric_limits<std::int64_t>::min()};
    std::int64_t decoded = encode_decode_little(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_little_double)
{
    double val{std::numeric_limits<double>::min()};
    double decoded = encode_decode_little(val);
    EXPECT_DOUBLE_EQ(val, decoded);

    val = std::numeric_limits<double>::max();
    decoded = encode_decode_little(val);
    EXPECT_DOUBLE_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_little_uint64_t)
{
    std::uint64_t val{std::numeric_limits<std::uint64_t>::max()};
    std::uint64_t decoded = encode_decode_little(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_int8_t)
{
    std::int8_t val{std::numeric_limits<std::int8_t>::min()};
    std::int8_t decoded = encode_decode_big(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_uint8_t)
{
    std::uint8_t val{std::numeric_limits<std::uint8_t>::max()};
    std::uint8_t decoded = encode_decode_big(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_int16_t)
{
    std::int16_t val{std::numeric_limits<std::int16_t>::min()};
    std::int16_t decoded = encode_decode_big(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_uint16_t)
{
    std::uint16_t val{std::numeric_limits<std::uint16_t>::max()};
    std::uint16_t decoded = encode_decode_big(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_int32_t)
{
    std::int32_t val{std::numeric_limits<std::int32_t>::min()};
    std::int32_t decoded = encode_decode_big(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_uint32_t)
{
    std::uint32_t val{std::numeric_limits<std::uint32_t>::max()};
    std::uint32_t decoded = encode_decode_big(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_int64_t)
{
    std::int64_t val{std::numeric_limits<std::int64_t>::min()};
    std::int64_t decoded = encode_decode_big(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_uint64_t)
{
    std::uint64_t val{std::numeric_limits<std::uint64_t>::max()};
    std::uint64_t decoded = encode_decode_big(val);
    EXPECT_EQ(val, decoded);
}

TEST(CodecTests, encode_decode_big_double)
{
    double val{std::numeric_limits<double>::min()};
    double decoded = encode_decode_big(val);
    EXPECT_DOUBLE_EQ(val, decoded);

    val = std::numeric_limits<double>::max();
    decoded = encode_decode_big(val);
    EXPECT_DOUBLE_EQ(val, decoded);
}

} // namespace byte_order::tests
