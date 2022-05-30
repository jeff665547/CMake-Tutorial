cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)
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

# Install the binary file of the library (e.g. *.dll).
option(INSTALL_DEPS "Automatically install the binary file of the shared or static library" ON)

include(FetchContent)
FetchContent_Declare(
    maths
    GIT_REPOSITORY http://gitlab.centrilliontech.com.tw:10088/centrillion/remoterepo.git # The link of the repository.
    GIT_TAG v0.1.0-fetchcontent
)
FetchContent_MakeAvailable(maths)

# Build from source (the following is same as FetchContent_MakeAvailable)
# FetchContent_GetProperties(maths)
# if (NOT maths_POPULATED)
#     FetchContent_Populate(maths)
# endif ()
# add_subdirectory(${maths_SOURCE_DIR} ${maths_BINARY_DIR})


# FetchContent -- primarily about bringing in external content (source code) and adding it to the build. 
# It has strong features for dependency management, but it lacks support for pre-built binaries.
# find_package() -- a complement to pre-built binaries, being primarily focused on bringing pre-built 
# binaries into the build but with no support for buing from source.
# A natural desire is to able to use pre-built binaries if available and fall back to building from source
# if not available. Basically try find_package() and if that fails, use FetchContent to fetch and build from
# the source.

add_executable(MathsDemo)
target_sources(MathsDemo
    PRIVATE
        main.cpp
)

target_link_libraries(MathsDemo
    PRIVATE
    maths_library
    status
)


# Install the MatheDemo application to the specified directory.
install(TARGETS MathsDemo
    EXPORT example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install the binary file of the shared library (e.g. *.dll).
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
# Shared library (UNIX): cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_INSTALL_PREFIX:PATH=../install
# Shared library (WIN): cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_INSTALL_PREFIX:PATH=../install
# Static library (UNIX): cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install
# Static library (WIN): cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install
# cmake --build . --target install