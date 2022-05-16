cmake_minimum_required(VERSION 3.15)

# ---------------------------------------------------------------------------------------
# Add a library target.
# ---------------------------------------------------------------------------------------
add_library(subtract_library subtract_header/subtract.h subtract.cpp)
target_link_libraries(subtract_library PUBLIC status)

# ---------------------------------------------------------------------------------------
# Specify the directories used for building/using executable.
# ---------------------------------------------------------------------------------------
target_include_directories(subtract_library PUBLIC subtract_header)