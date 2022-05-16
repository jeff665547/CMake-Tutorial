cmake_minimum_required(VERSION 3.15)
project(HelloInstalling)

# Install the binary file of the shared library (e.g. *.dll).
option(INSTALL_DEPS "Automatically install the binary file of the shared or static library" ON)

find_package(maths CONFIG REQUIRED)
find_package(fmt   CONFIG REQUIRED)

add_executable(MathsDemo)
target_sources(MathsDemo
    PRIVATE
        main.cpp
)

target_link_libraries(MathsDemo
    PRIVATE
        Maths::maths_library
        Maths::status
        fmt::fmt
)


# Install the MatheDemo application to the specified directory.
install(TARGETS MathsDemo
    EXPORT example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


if(INSTALL_DEPS)
    if(WIN32)
        configure_file(
            cmake/bundle.cmake.in 
            ${CMAKE_BINARY_DIR}/bundle.cmake @ONLY
        )
    endif()
    install(
        SCRIPT ${CMAKE_BINARY_DIR}/bundle.cmake
    )
endif()

# CMake commands: 
# Shared library: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH="../install" -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic"
# Static library: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH="../install" -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-static"
# For locally experimental build: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH="../install" -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic" -DVCPKG_OVERLAY_PORTS="../../vcpkg-registries/ports/maths"
# cmake --build . --target install
