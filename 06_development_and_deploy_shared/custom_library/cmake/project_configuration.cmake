cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # Used for the debug feature.
set(CMAKE_VERBOSE_MAKEFILE OFF)        # Used for the debug feature.
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # Used for the -std=c++XX flag.
set(CMAKE_CXX_EXTENSIONS OFF)          # Used for the -std=c++XX flag.

# 1. Use an INTERFACE target to encapsulate compiler configuration 
#    – all of the warning flags, optimization level and whatever else necessary.
# 2. Linked into other targets to ensure the consistent configuration.
add_library(ProjectConfiguration INTERFACE)
target_compile_options(ProjectConfiguration 
    INTERFACE
        -O3 
        -Wall 
        -Wextra
        $<$<COMPILE_LANGUAGE:CXX>:-Weffc++>
)
target_compile_definitions(ProjectConfiguration
    INTERFACE
        cxx_std_17  # for -std=c++17
)