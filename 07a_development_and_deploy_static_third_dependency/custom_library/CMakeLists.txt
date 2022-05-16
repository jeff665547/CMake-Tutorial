cmake_minimum_required(VERSION 3.15)

project(development_and_deploy VERSION 0.1.0)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

option(BUILD_EXAMPLE "Build the example target." ON)
option(PKG_INSTALL "Install (distribute) this package" ON)

set(PKG_CONFIG_REQUIRES spdlog)  # This is set for building the *.pc file

include(cmake/project_configuration.cmake)
include(GNUInstallDirs)

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
            status
    )
endif()

# CMake commands:  
# cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=../install -DBUILD_TESTING:BOOL=ON
# cmake --build . --target install