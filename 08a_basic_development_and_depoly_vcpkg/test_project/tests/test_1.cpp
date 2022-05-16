#include <gtest/gtest.h>
#include <fmt/core.h>

TEST(tt, addTest){
    fmt::print("The version of the fmt library is {}.\n", FMT_VERSION);
    const int result = 42 + 11;
    EXPECT_EQ(result, 42 + 11);
}

TEST(tt, subTest){
    fmt::print("Hello World, the following answer is {}.!\n", 42 - 11);
    const int result = 42 - 11;
    EXPECT_EQ(result, 42 - 11);
}