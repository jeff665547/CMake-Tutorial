cmake_minimum_required(VERSION 3.18)
project(ManifestsModeDemo CXX)

option(INSTALL_DEPS "Automatically install the binary file of the shared or static library" ON)

find_package(fmt CONFIG REQUIRED)

add_executable(ManifestDemo)
target_sources(ManifestDemo
    PRIVATE
        main.cpp
)

target_link_libraries(ManifestDemo
    PRIVATE
        fmt::fmt
)

include(CTest)
add_subdirectory(tests)

# Install the ManifestDemo application (.exe) to the specified directory.
install(TARGETS ManifestDemo
    EXPORT example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install the binary file of the shared library (e.g. *.dll).
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
# Shared library: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic"
# Static library: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-static"
# cmake --build . --target install