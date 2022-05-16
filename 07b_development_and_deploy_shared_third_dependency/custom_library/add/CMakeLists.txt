cmake_minimum_required(VERSION 3.15)
add_library(add_library add_header/add.h add.cpp)

target_link_libraries(
    add_library
    PUBLIC
        status
    PRIVATE
        ProjectConfiguration
)
target_include_directories(
    add_library 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(PKG_INSTALL)
    install(
        TARGETS add_library
        EXPORT Maths
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(
        DIRECTORY add_header
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()