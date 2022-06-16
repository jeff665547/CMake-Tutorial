cmake_minimum_required(VERSION 3.15)
project(basic_development)

# ---------------------------------------------------------------------------------------
# Add the executable target.
# ---------------------------------------------------------------------------------------
add_executable(basic_development_main add.h calc_status.h add.cpp main.cpp)

target_compile_features(basic_development_main PUBLIC cxx_std_11)

# CMake commands:
# UNIX: cmake .. -DCMAKE_BUILD_TYPE:STRING=Release
# WIN: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release
# cmake --build .