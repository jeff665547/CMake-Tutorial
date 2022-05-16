#include <gtest/gtest.h>
#include <maths.h>

TEST(maths, addTest){
    Maths::calc_status cs{};
    const int result = Maths::add(42, 11, cs);
    EXPECT_EQ(cs, Maths::calc_status::success);
    EXPECT_EQ(result, 42 + 11);
}

TEST(maths, subTest){
    Maths::calc_status cs{};
    const int result = Maths::subtract(42, 11, cs);
    EXPECT_EQ(cs, Maths::calc_status::success);
    EXPECT_EQ(result, 42 - 11);
}