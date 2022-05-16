cmake_minimum_required(VERSION 3.15)
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
)

set(INSTALL_GTEST ON)  # Enable gtest calling install for its own targets.
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

# ldd can help analyze the dependencies.
set(deps gtest gtest_main maths_library add_library subtract_library)

# Copy the dependencies used for building the test target after the binary is built (if we build the shared libraries).
if(BUILD_SHARED_LIBS)
    foreach(elem ${deps})
        add_custom_command(
            TARGET testMaths 
            POST_BUILD 
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${elem}> ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_NAME:${elem}>
        )
    endforeach()
endif()

include(GoogleTest)

gtest_discover_tests(testMaths)