#include <gtest/gtest.h>

#include "byte_order/ByteOrder.hpp"

namespace byte_order::tests {

TEST(ByteOrderTests, expected_byte_order)
{
    const int val{1};
    const int native = reinterpret_cast<const char *>(&val)[0];

    ByteOrder expected = (native == 1) ? ByteOrder::little : ByteOrder::big;
    EXPECT_EQ(expected, ByteOrder::native);
}

} // namespace byte_order::tests
