cmake_minimum_required(VERSION 3.15)
project(HelloInstalling)
include(GNUInstallDirs)

if (UNIX)
    file(RELATIVE_PATH relativeRpath
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    )
    set(run_time_exe_dir $<IF:$<PLATFORM_ID:Darwin>,@loader_path,$ORIGIN>)
    set(CMAKE_INSTALL_RPATH "${run_time_exe_dir}" "${run_time_exe_dir}/${relativeRpath}")
endif (UNIX)

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
        maths::maths_library
        maths::status
        fmt::fmt
)

target_compile_features(MathsDemo
    PRIVATE
        cxx_std_17
)

# Install the MatheDemo application to the specified directory.
install(TARGETS MathsDemo
    EXPORT example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


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
# Shared library (UNIX): cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-linux-dynamic" -DVCPKG_OVERLAY_TRIPLETS="../../custom-triplets"
# Shared library (WIN): cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH="../install" -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic"
# Static library (UNIX): cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-linux-static" -DVCPKG_OVERLAY_TRIPLETS="../../custom-triplets"
# Static library (WIN): cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH="../install" -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-static"
# For locally experimental build: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH="../install" -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic" -DVCPKG_OVERLAY_PORTS="../../vcpkg-registries/ports/maths"
# cmake --build . --target install
