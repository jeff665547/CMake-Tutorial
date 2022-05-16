# ---------------------------------------------------------------------------------------
# Use FetchContent to download the source of the external content.
# ---------------------------------------------------------------------------------------
include(FetchContent)  # Download (Fetch) arbitrary external content (e.g. another C/C++ project or scripts)
                       # for the purpose of incorporating it into a project. It is a very useful tool for 
                       # managing external dependencies built with our project.

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)  # This processes the declared content above.

# To prevent FetchContent from verifying if the declared dependencies are up to date everytime we build the project.
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "")

add_executable(testMaths basic_math.cpp)

target_link_libraries(
    testMaths
    PRIVATE
        maths_library
        ProjectConfiguration
        gtest                         # Declared by the googletest project from FetchContent
        gtest_main                    # Declared by the googletest project from FetchContent
)

# ---------------------------------------------------------------------------------------
# Use GoogleTest to register separate tests for each test case defined in the test suite.
# ---------------------------------------------------------------------------------------
# add_test(NAME testMaths COMMAND testMaths)

include(GoogleTest)

gtest_discover_tests(testMaths)       # Provide by the GoogleTest via the include(GoogleTest) command.
                                      # It replaces "add_test" command for tests written using googletest.
                                      # To run test, use the "ctest -V" command.