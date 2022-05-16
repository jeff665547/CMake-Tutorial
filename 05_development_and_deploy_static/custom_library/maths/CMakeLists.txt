cmake_minimum_required(VERSION 3.15)
add_library(maths_library maths_header/maths.h maths.cpp)
target_link_libraries(
    maths_library 
    PUBLIC 
        add_library 
        subtract_library
    PRIVATE
        ProjectConfiguration
)
target_include_directories(
    maths_library 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>           # Fix the relative build and install directory issue.
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(PKG_INSTALL)
    install(
    	TARGETS maths_library                                    # -> Adding the target (maths_library) to the following export target.
        EXPORT Maths                                             # -> Loads the Maths export target with all the necessary information.
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(
    	DIRECTORY maths_header                                   # Manaually install and expose the header file for this current module.
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()