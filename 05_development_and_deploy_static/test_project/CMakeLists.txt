cmake_minimum_required(VERSION 3.15)
project(HelloInstalling)

find_package(Maths 0.1.0)

add_executable(MathsDemo)
target_sources(MathsDemo
    PRIVATE
        main.cpp
)

target_link_libraries(MathsDemo
    PRIVATE
        Maths::maths_library
)

target_compile_features(MathsDemo PUBLIC cxx_std_17)

# CMake commands: 
# UNIX: cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_PREFIX_PATH:PATH=../custom_library/install/lib/cmake
# WIN: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_PREFIX_PATH:PATH=../custom_library/install/lib/cmake
# cmake --build .