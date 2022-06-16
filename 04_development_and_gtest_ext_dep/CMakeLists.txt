cmake_minimum_required(VERSION 3.15)
project(development_and_gtest_ext_dep)

include(cmake/project_configuration.cmake)

add_subdirectory(status)
add_subdirectory(add)
add_subdirectory(subtract)
add_subdirectory(maths)

if (BUILD_TESTING)
    # ---------------------------------------------------------------------------------------
    # Enable CTest.
    # ---------------------------------------------------------------------------------------
    # enable_testing() is a degrade command, and can only enable the basic use of the ctest 
    # command line tool. include(CTest) also define a BUILD_TESTING option and provide the 
    # integration with CDash.
    include(CTest)
    add_subdirectory(tests)
endif()

add_executable(development_and_gtest_ext_dep_main main.cpp)
target_link_libraries(development_and_gtest_ext_dep_main
    PRIVATE 
        maths_library
        ProjectConfiguration
)

# CMake commands:
# UNIX: cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_TESTING:BOOL=ON
# WIN: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_TESTING:BOOL=ON
# cmake --build . 