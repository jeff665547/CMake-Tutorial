cmake_minimum_required(VERSION 3.15)

# ---------------------------------------------------------------------------------------
# Add a version for this library.
# ---------------------------------------------------------------------------------------
project(development_and_deploy VERSION 0.1.0)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)                # Fix the the break issue from the FetchContent or git submodules failed to build a sub-project.

# ---------------------------------------------------------------------------------------
# Add options to control the script.
# ---------------------------------------------------------------------------------------
option(BUILD_EXAMPLE "Build the example target." ON)
option(PKG_INSTALL "Install (distribute) this package" ON)

set(PKG_CONFIG_REQUIRES spdlog)  # This is set for building the *.pc file

include(cmake/project_configuration.cmake)
include(GNUInstallDirs)                              # -> For deploying into different platforms.

add_subdirectory(status)
add_subdirectory(add)
add_subdirectory(subtract)
add_subdirectory(maths)

if (BUILD_TESTING)
    include(CTest)
    add_subdirectory(tests)
endif()

# ---------------------------------------------------------------------------------------
# Install (Deploy) the package.
# ---------------------------------------------------------------------------------------
if(PKG_INSTALL)
    message(STATUS "Generating install")
    set(pkg_config_in "${CMAKE_CURRENT_LIST_DIR}/cmake/MathsConfig.cmake.in")
    set(pkg_config_out "${CMAKE_CURRENT_BINARY_DIR}/MathsConfig.cmake")
    set(pkg_config_targets_file "MathsConfigTargets.cmake")
    set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/MathsConfigVersion.cmake")
    set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/Maths")
    set(pkgconfig_install_dir "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
    set(pkg_config "${CMAKE_BINARY_DIR}/Maths.pc")

    # ---------------------------------------------------------------------------------------
    # Install and export targets CMake config files (for the downstream importing Maths library)
    # ---------------------------------------------------------------------------------------
    install(
        TARGETS ProjectConfiguration                                         # -> Loads the Maths export target with all the necessary information.
        EXPORT Maths
    )
    install(
        EXPORT Maths                                                         # -> Exposes all the necessary information to the user. 
                                                                             #    (An Export target carries the full info about properties of each target 
                                                                             #     and all the inter-target dependencies.)
        DESTINATION ${export_dest_dir}
        NAMESPACE Maths::                                                    # -> Avoid name clashes with other packages. 
                                                                             #    (All targets exposed by the installed EXPORT target 
                                                                             #     will have the given prefix Maths::. This indicates
                                                                             #     the end user of our library will need to include the 
                                                                             #     add_library by linking Maths::add_library.)
        FILE ${pkg_config_targets_file}
    )

    # ---------------------------------------------------------------------------------------
    # Install pkg-config file (for other build systems)
    # ---------------------------------------------------------------------------------------
    # PKG_CONFIG_DEFINES is set for building the *.pc file
    get_target_property(PKG_CONFIG_DEFINES maths_library INTERFACE_COMPILE_DEFINITIONS)
    string(REPLACE ";" " -D" PKG_CONFIG_DEFINES ${PKG_CONFIG_DEFINES})
    string(CONCAT PKG_CONFIG_DEFINES "-D" "${PKG_CONFIG_DEFINES}")
    configure_file("cmake/Maths.pc.in" "${pkg_config}" @ONLY)
    install(FILES ${pkg_config} DESTINATION ${pkgconfig_install_dir})

    # ---------------------------------------------------------------------------------------
    # Install CMake package config files (for using find_packages() in the downstream use cases.)
    # ---------------------------------------------------------------------------------------
    include(CMakePackageConfigHelpers)
    configure_package_config_file(                                           # Creating Config files that can be imported by other projects to find and use as a package.
        ${pkg_config_in} ${pkg_config_out}                                   # -> The template file (pkg_config_in) that is used to generate the package config file.
                                                                             # -> The Destination (pkg_config_out) where the generated Config file will be stored 
                                                                             #    (this is generated by the template file).
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR                                   # -> Set the variables which contain the install destination. It will be passed 
                                                                             #    into the template file as the PACKAGE_CMAKE_INSTALL_INCLUDEDIR variable.
                                                                             #    It ensures that the path is correctly expanded to a path prefixed in the 
                                                                             #    package installation directory. It is calculated by 
                                                                             #    configure_package_config_file so that they are always relative to the 
                                                                             #    installed location of the package.
        INSTALL_DESTINATION ${export_dest_dir}                               # -> The destination where the generated Config file will be installed.
    )

    write_basic_package_version_file(                                        # Create the version file.
        ${version_config_file}
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion                                       # Compatibility of this current library for the downstream package. It lets find_package to 
                                                                             # determine if the package found is compatible with the one requested by the downstream project.
                                                                             # SameMajorVersion is compatible with the semver concept.
    )
    install(
        FILES ${pkg_config_out} ${version_config_file}                       # Install the generated Config file to the specified path.
        DESTINATION ${export_dest_dir}
    )

    # ---------------------------------------------------------------------------------------
    # Support the creation of installable packages
    # ---------------------------------------------------------------------------------------
    # include(cmake/MathsCPack.cmake)
endif()

# The following will not be used for building a library. Just an application.
if(BUILD_EXAMPLE)
    add_executable(development_and_deploy_main main.cpp)
    target_link_libraries(development_and_deploy_main
        PRIVATE 
            maths_library
            ProjectConfiguration
    )
endif()

# CMake commands:
# cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=../install -DBUILD_TESTING:BOOL=ON
# cmake --build . --target install