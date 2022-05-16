cmake_minimum_required(VERSION 3.15)
add_library(add_library add_header/add.h add.cpp)

# ---------------------------------------------------------------------------------------
# Specify the dependency and some properties used for building the executable target.
# ---------------------------------------------------------------------------------------
target_link_libraries(add_library
    PUBLIC
        status
    PRIVATE
        ProjectConfiguration)
target_include_directories(add_library PUBLIC add_header)