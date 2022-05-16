cmake_minimum_required(VERSION 3.15)
include(FetchContent)

# FetchContent_Declare(
#     googletest
#     GIT_REPOSITORY https://github.com/google/googletest.git
#     GIT_TAG release-1.10.0
# )

# set(INSTALL_GTEST OFF)                  # Disable gtest calling install for its own targets.
# FetchContent_MakeAvailable(googletest)

# set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "")
find_package(GTest REQUIRED)

add_executable(testing_target test_1.cpp)

target_link_libraries(
    testing_target
    PRIVATE
        fmt::fmt
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(testing_target)