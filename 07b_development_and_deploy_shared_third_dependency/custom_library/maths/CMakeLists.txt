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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(PKG_INSTALL)
    install(
        TARGETS maths_library
        EXPORT Maths
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(
        DIRECTORY maths_header
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()