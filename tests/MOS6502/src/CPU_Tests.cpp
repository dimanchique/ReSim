#include "MOS6502_TestingSuite.h"

class UtilsTests : public testing::Test {};

TEST_F(UtilsTests, PageCrossingTest) {
    EXPECT_TRUE(IsPageCrossed(0x4001, 0x3ffe));
    EXPECT_TRUE(IsPageCrossed(0x4001, 0x4101));
    EXPECT_FALSE(IsPageCrossed(0x4001, 0x4005));
    EXPECT_FALSE(IsPageCrossed(0x3333, 0x3335));
}

TEST_F(UtilsTests, DataConversionTest) {
    EXPECT_EQ((BYTE) 45, (SBYTE) 45);
    EXPECT_NE((BYTE) 250, (SBYTE) 250);
    EXPECT_EQ((BYTE) 258, 0x2);
    EXPECT_EQ((SBYTE) 253, -3);
}
