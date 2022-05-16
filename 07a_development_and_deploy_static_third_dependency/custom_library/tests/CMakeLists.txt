cmake_minimum_required(VERSION 3.15)
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
)

set(INSTALL_GTEST OFF)  # Disable gtest calling install for its own targets.
FetchContent_MakeAvailable(googletest)

# FetchContent_Declare(
#     spdlog 
#     URL https://github.com/gabime/spdlog/archive/refs/tags/v1.9.2.zip # The link of the source code.
# )

# FetchContent_MakeAvailable(spdlog)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "")

add_executable(testMaths basic_math.cpp)

target_link_libraries(
    testMaths
    PRIVATE
        maths_library
        ProjectConfiguration
        gtest
        gtest_main
        spdlog
)

include(GoogleTest)

gtest_discover_tests(testMaths)