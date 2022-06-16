cmake_minimum_required(VERSION 3.15)
project(modular_development)

# ---------------------------------------------------------------------------------------
# Change the current working directory to the subdirectory to run the CMake script under
# each subdirectory.
# ---------------------------------------------------------------------------------------
add_subdirectory(status)
add_subdirectory(add)
add_subdirectory(subtract)
add_subdirectory(maths)

# ---------------------------------------------------------------------------------------
# Add the executable target.
# ---------------------------------------------------------------------------------------
add_executable(modular_development_main main.cpp)

# ---------------------------------------------------------------------------------------
# Specify the dependency or some properties used for building the executable target.
# ---------------------------------------------------------------------------------------
target_link_libraries(modular_development_main PRIVATE maths_library)

target_compile_features(modular_development_main PRIVATE cxx_std_11)

# CMake commands:
# UNIX: cmake .. -DCMAKE_BUILD_TYPE:STRING=Release 
# WIN: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release
# cmake --build . 