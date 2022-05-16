cmake_minimum_required(VERSION 3.15)

project(modular_development_custom_compile)

# ---------------------------------------------------------------------------------------
# Load and run CMake code from a CMake file.
# ---------------------------------------------------------------------------------------
include(cmake/project_configuration.cmake)

add_subdirectory(status)
add_subdirectory(add)
add_subdirectory(subtract)
add_subdirectory(maths)

add_executable(modular_development_custom_compile_main main.cpp)

# ---------------------------------------------------------------------------------------
# Specify the dependency and some property used for building the executable target.
# ---------------------------------------------------------------------------------------
target_link_libraries(modular_development_custom_compile_main 
    PRIVATE 
        maths_library
        ProjectConfiguration
)

# CMake commands:
# cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release
# cmake --build . 