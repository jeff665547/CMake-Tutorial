cmake_minimum_required(VERSION 3.15)
project(HelloInstalling)

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
    if(WIN32)
        configure_file(
            cmake/bundle.cmake.in 
            ${CMAKE_BINARY_DIR}/bundle.cmake @ONLY
        )
    endif()
    install(
        SCRIPT ${CMAKE_BINARY_DIR}/bundle.cmake
    )
endif()

# CMAKE commands: 
# cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_PREFIX_PATH:PATH=../custom_library/install/lib/cmake -DCMAKE_INSTALL_PREFIX:PATH=../install
# cmake --build . --target install