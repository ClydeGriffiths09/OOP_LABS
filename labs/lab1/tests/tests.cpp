#include <gtest/gtest.h>
#include "../include/eliminate_bits.h"

TEST(EliminateUnsetBitsTest, BasicTests) {
    EXPECT_EQ(eliminate_unset_bits("1101010101010101"), 511);
    EXPECT_EQ(eliminate_unset_bits("111"), 7);
    EXPECT_EQ(eliminate_unset_bits("1000000"), 1);
    EXPECT_EQ(eliminate_unset_bits("000"), 0);
}

TEST(EliminateUnsetBitsTest, SingleOne) {
    EXPECT_EQ(eliminate_unset_bits("1"), 1);
    EXPECT_EQ(eliminate_unset_bits("0"), 0);
}

TEST(EliminateUnsetBitsTest, MixedCases) {
    EXPECT_EQ(eliminate_unset_bits("1010101"), 15);
    EXPECT_EQ(eliminate_unset_bits("111000"), 7);
    EXPECT_EQ(eliminate_unset_bits("001010"), 3);
}

TEST(EliminateUnsetBitsTest, AllOnes) {
    EXPECT_EQ(eliminate_unset_bits("1111"), 15);
    EXPECT_EQ(eliminate_unset_bits("11111"), 31);
    EXPECT_EQ(eliminate_unset_bits("111111"), 63);
}

TEST(EliminateUnsetBitsTest, AllZeros) {
    EXPECT_EQ(eliminate_unset_bits("0000"), 0);
    EXPECT_EQ(eliminate_unset_bits("00"), 0);
}

TEST(EliminateUnsetBitsTest, LongStrings) {
    EXPECT_EQ(eliminate_unset_bits("1111111111"), 1023);
    EXPECT_EQ(eliminate_unset_bits("111111111111111"), 32767);
}
