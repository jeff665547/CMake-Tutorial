cmake_minimum_required(VERSION 3.15)

# ---------------------------------------------------------------------------------------
# Add a library target.
# ---------------------------------------------------------------------------------------
add_library(add_library add_header/add.h add.cpp)
target_link_libraries(add_library PUBLIC status)

# ---------------------------------------------------------------------------------------
# Specify the directories used for building/using executable.
# ---------------------------------------------------------------------------------------
target_include_directories(add_library PUBLIC add_header)
message(STATUS "This is the current source directory. ${CMAKE_CURRENT_SOURCE_DIR}")  # Print the information used in CMake.