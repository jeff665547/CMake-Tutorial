cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)
project(HelloInstalling)
include(GNUInstallDirs)

if (UNIX)
    file(RELATIVE_PATH relativeRpath
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    )
    set(run_time_exe_dir $<IF:${APPLE},@loader_path,$ORIGIN>)
    set(CMAKE_INSTALL_RPATH "${run_time_exe_dir}" "${run_time_exe_dir}/${relativeRpath}")
endif (UNIX)

# Install the binary file of the library (e.g. *.dll).
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
        Maths::status
)


# Install the MatheDemo application to the specified directory.
install(TARGETS MathsDemo                                # -> Adding the target (MathsDemo) to the following export target.
    EXPORT example                                       # -> Loads the example export target with all the necessary information.
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

# CMAKE commands: 
# UNIX: cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_PREFIX_PATH:PATH=../custom_library/install/lib/cmake -DCMAKE_INSTALL_PREFIX:PATH=../install
# WIN: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_PREFIX_PATH:PATH=../custom_library/install/lib/cmake -DCMAKE_INSTALL_PREFIX:PATH=../install
# cmake --build . --target install
