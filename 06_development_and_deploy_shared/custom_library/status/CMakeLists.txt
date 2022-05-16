cmake_minimum_required(VERSION 3.15)
add_library(status INTERFACE)
target_include_directories(
    status 
    INTERFACE         
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>            # Fix the relative build and install directory issue.
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(PKG_INSTALL)
    install(
    	TARGETS status                                        # -> Adding the target (status) to the following export target.
        EXPORT Maths                                          # -> Loads the Maths export target with all the necessary information.
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/calc_status.h       # Manaually install and expose the header file for this current module.
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()