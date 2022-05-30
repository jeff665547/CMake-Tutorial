cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 11)
project(ApplicationDemo CXX)
include(GNUInstallDirs)

if (UNIX)
    file(RELATIVE_PATH relativeRpath
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    )
    set(run_time_exe_dir $<IF:${APPLE},@loader_path,$ORIGIN>)
    set(CMAKE_INSTALL_RPATH "${run_time_exe_dir}" "${run_time_exe_dir}/${relativeRpath}")
endif (UNIX)

option(INSTALL_DEPS "Automatically install the binary file of the shared or static library" ON)

find_package(fmt REQUIRED)

add_executable(Application)
target_sources(Application
    PRIVATE
        main.cpp
)

target_link_libraries(Application
    PRIVATE
        fmt::fmt
)

include(CTest)
add_subdirectory(tests)

# Install the Application application (.exe) to the specified directory.
install(TARGETS Application
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
# (WIN) cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_MODULE_PATH="C:/Cppdev/CMake_tutorial_example/08b_basic_development_and_depoly_conan/test_project/build"
# (UNIX) cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_MODULE_PATH="~/cmake-tutorial/08b_basic_development_and_depoly_conan/test_project/build"
# Shared library and static library can be switched via conanfile.txt or specified through the [options] area under the profile 
# file (@ Users/[username]/.conan/profiles).
# cmake --build . --target install
