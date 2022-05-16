#include <gtest/gtest.h>
#include <maths_header/maths.h>
#include <spdlog/spdlog.h>

TEST(maths, addTest){
    Maths::calc_status cs{};
    const int result = Maths::add(42, 11, cs);
    EXPECT_EQ(cs, Maths::calc_status::success);
    EXPECT_EQ(result, 42 + 11);
}

TEST(maths, subTest){
    spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
    Maths::calc_status cs{};
    const int result = Maths::subtract(42, 11, cs);
    EXPECT_EQ(cs, Maths::calc_status::success);
    EXPECT_EQ(result, 42 - 11);
}
