cmake_minimum_required(VERSION 3.15)

project(development_and_deploy VERSION 0.1.0)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

option(BUILD_EXAMPLE "Build the example target." ON)
option(PKG_INSTALL "Install (distribute) this package" ON)

set(PKG_CONFIG_REQUIRES spdlog)  # This is set for building the *.pc file

include(cmake/project_configuration.cmake)
include(GNUInstallDirs)

# This is for building shared libraries. This needs be configured before any targets are created.
# This will update and install the runtime paths of the shared library. (for Unix platforms.)
#
# In Windows, the DLLs should generally be installed alongside the application binaries, in 
# the same directory.
# 1. If the library is only used by this program, it should be in that program’s directory.
#    In this case, the DLL won't interfere with any other on the system that happens to 
#    have the same name.
# 2. If the library is to be made available to other programs, it should be under 
#    %CommonProgramFiles% or %CommonProgramFiles(x86)%. For example, ‘VST2’ and ‘VST3’ 
#    folders here would be for audio plugins for music production software.
# 3. If the library is a system extension or enhancement, it should be under 
#    %windir%\system32 or standing alone in its own directory under %ProgramFiles% 
#    or %ProgramFiles(x86)%. I normally opt for the latter.
#
# ---------------------------------------------------------------------------------------
# Automatically set the CMAKE_INSTALL_RPATH (runtime path) path for the UNIX system for 
# building shared lib, so that users can find the installed library.
# ---------------------------------------------------------------------------------------
if (UNIX)
    file(RELATIVE_PATH relativeRpath
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    )
    set(CMAKE_INSTALL_RPATH $ORIGIN $ORIGIN/${relativeRpath})
endif (UNIX)

# Control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(status)
add_subdirectory(add)
add_subdirectory(subtract)
add_subdirectory(maths)

if (BUILD_TESTING)
    include(CTest)
    add_subdirectory(tests)
endif()

if(PKG_INSTALL)
    message(STATUS "Generating install")
    set(pkg_config_in "${CMAKE_CURRENT_LIST_DIR}/cmake/MathsConfig.cmake.in")
    set(pkg_config_out "${CMAKE_CURRENT_BINARY_DIR}/MathsConfig.cmake")
    set(pkg_config_targets_file "MathsConfigTargets.cmake")
    set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/MathsConfigVersion.cmake")
    set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/Maths")
    set(pkgconfig_install_dir "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
    set(pkg_config "${CMAKE_BINARY_DIR}/Maths.pc")

    install(
        TARGETS ProjectConfiguration
        EXPORT Maths
    )
    install(
        EXPORT Maths
        DESTINATION ${export_dest_dir}
        NAMESPACE Maths::
        FILE ${pkg_config_targets_file}
    )

    get_target_property(PKG_CONFIG_DEFINES maths_library INTERFACE_COMPILE_DEFINITIONS)
    string(REPLACE ";" " -D" PKG_CONFIG_DEFINES ${PKG_CONFIG_DEFINES})
    string(CONCAT PKG_CONFIG_DEFINES "-D" "${PKG_CONFIG_DEFINES}")
    configure_file("cmake/Maths.pc.in" "${pkg_config}" @ONLY)
    install(FILES ${pkg_config} DESTINATION ${pkgconfig_install_dir})

    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        ${pkg_config_in} ${pkg_config_out}
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR
        INSTALL_DESTINATION ${export_dest_dir}
    )

    write_basic_package_version_file(
        ${version_config_file}
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )
    install(
        FILES ${pkg_config_out} ${version_config_file}
        DESTINATION ${export_dest_dir}
    )

endif()

# The following will not be used for building a library. Just an application.
if(BUILD_EXAMPLE)
    add_executable(development_and_deploy_main main.cpp)
    target_link_libraries(development_and_deploy_main
        PRIVATE 
            maths_library
            ProjectConfiguration
    )
    if(BUILD_SHARED_LIBS)
        set(deps maths_library add_library subtract_library)
        foreach(elem ${deps})
            add_custom_command(
                TARGET development_and_deploy_main 
                POST_BUILD 
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${elem}> ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_NAME:${elem}>
            )
        endforeach()
    endif()
endif()

# CMake command:
# UNIX: cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_INSTALL_PREFIX:PATH=../install -DBUILD_TESTING:BOOL=ON 
# WIN: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_INSTALL_PREFIX:PATH=../install -DBUILD_TESTING:BOOL=ON
# cmake --build . --target install