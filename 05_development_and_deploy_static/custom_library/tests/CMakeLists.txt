cmake_minimum_required(VERSION 3.15)
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
)

FetchContent_MakeAvailable(googletest)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "")

add_executable(testMaths basic_math.cpp)

target_link_libraries(
    testMaths
    PRIVATE
        maths_library
        ProjectConfiguration
        gtest
        gtest_main
)

include(GoogleTest)

gtest_discover_tests(testMaths)