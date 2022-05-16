cmake_minimum_required(VERSION 3.15)
add_library(maths_library maths_header/maths.h maths.cpp)

# ---------------------------------------------------------------------------------------
# Specify the dependencies and some properties used for building the executable target.
# ---------------------------------------------------------------------------------------
target_link_libraries(maths_library 
    PUBLIC 
        add_library 
        subtract_library
    PRIVATE
        ProjectConfiguration
)
target_include_directories(maths_library 
    PUBLIC 
        maths_header
)