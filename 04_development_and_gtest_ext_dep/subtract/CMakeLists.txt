cmake_minimum_required(VERSION 3.15)
add_library(subtract_library subtract_header/subtract.h subtract.cpp)
target_link_libraries(subtract_library 
    PUBLIC 
        status
    PRIVATE
        ProjectConfiguration)
target_include_directories(subtract_library PUBLIC subtract_header)