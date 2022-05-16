cmake_minimum_required(VERSION 3.15)
add_library(subtract_library subtract_header/subtract.h subtract.cpp)
target_link_libraries(
    subtract_library 
    PUBLIC 
        status
    PRIVATE
        ProjectConfiguration
)

target_include_directories(
    subtract_library 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(PKG_INSTALL)
    install(
        TARGETS subtract_library
        EXPORT Maths
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(
        DIRECTORY subtract_header
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()