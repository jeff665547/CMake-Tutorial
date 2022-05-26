cmake_minimum_required(VERSION 3.15)
project(HelloInstalling)

# Install the binary file of the shared library (e.g. *.dll).
option(INSTALL_DEPS "Automatically install the binary file of the shared or static library" ON)

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

# -------------------------------------------------------------------------------------------------------
# Automatically analyze the dependency and copy those binaries next to the MathsDemo executable manually.
# -------------------------------------------------------------------------------------------------------
# The *.dll file of the library (Maths::maths_library) will be copied from the specified directory.
if(INSTALL_DEPS)
    configure_file(
        "cmake/${CMAKE_HOST_SYSTEM_NAME}/bundle.cmake.in" 
        "${CMAKE_BINARY_DIR}/bundle.cmake" @ONLY
    )
    install(
        SCRIPT "${CMAKE_BINARY_DIR}/bundle.cmake"
    )
endif()

# CMake commands: 
# UNIX: cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_PREFIX_PATH:PATH=../custom_library/install/lib/cmake
# WIN: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_PREFIX_PATH:PATH=../custom_library/install/lib/cmake
# cmake --build . --target install