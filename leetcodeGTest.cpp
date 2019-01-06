#include "962_MaximumWidthRamp/MaximumWidthRamp.h"
#include "970_PowerfulIntegers/PowerfulIntegers.h"
#include "gtest/gtest.h"

TEST(leetcode962tests, tests) {
    Solution962_4 s;
    vector<int> in962_1{6,0,8,2,1,5};
    vector<int> in962_2{9,8,1,0,1,9,4,0,4,1};
    vector<int> in962_3{0,0};
    vector<int> in962_4{1,0};
    vector<int> in962_5{9,9,8,8,7,7};
    vector<int> in962_6{1,2,3,4,5,6};
    vector<int> in962_7{6,5,4,3,2,1};
    vector<int> in962_8{0,0,9,9,5,5};
    vector<int> in962_9{3,28,15,1,4,12,6,19,8,15,3,9,6,4,13,12,6,12,10,1,2,1,4,1,4,0,0,1,1,0};
    EXPECT_EQ(s.maxWidthRamp(in962_1), 4);
    EXPECT_EQ(s.maxWidthRamp(in962_2), 7);
    EXPECT_EQ(s.maxWidthRamp(in962_3), 1);
    EXPECT_EQ(s.maxWidthRamp(in962_4), 0);
    EXPECT_EQ(s.maxWidthRamp(in962_5), 1);
    EXPECT_EQ(s.maxWidthRamp(in962_6), 5);
    EXPECT_EQ(s.maxWidthRamp(in962_7), 0);
    EXPECT_EQ(s.maxWidthRamp(in962_8), 5);
    EXPECT_EQ(s.maxWidthRamp(in962_9), 25);

}

TEST(leetcode970Tests, tests) {
    Solution970 s;

    vector<int> out1{2,3,4,5,7,9,10};
    EXPECT_EQ(s.powerfulIntegers(2,3,10), out1);
    EXPECT_EQ(s.powerfulIntegers(1, 1, 0), vector<int>{});
    EXPECT_EQ(s.powerfulIntegers(1,1,1), vector<int>{});
//    EXPECT_EQ(s.powerfulIntegers(1,2,100), vector<int>{});
}
