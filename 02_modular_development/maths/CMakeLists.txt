cmake_minimum_required(VERSION 3.15)

# ---------------------------------------------------------------------------------------
# Add a library target.
# ---------------------------------------------------------------------------------------
add_library(maths_library maths_header/maths.h maths.cpp)
target_link_libraries(maths_library PUBLIC add_library subtract_library)

# ---------------------------------------------------------------------------------------
# Specify the directories used for building/using executable.
# ---------------------------------------------------------------------------------------
target_include_directories(maths_library PUBLIC maths_header)