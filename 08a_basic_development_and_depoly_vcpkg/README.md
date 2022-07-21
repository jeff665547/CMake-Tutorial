0. Prerequisites
    * OS: Windows7 or newer
    * OS: macOS 10.14 or below with homebrew.
    * Git
    * g++ >= 6

1. Preparation for the (MinGW-w64) compiler:
    * Install native MinGW-w64 from SourceForge.net. (demonstrated in this test_project) (Could generate some unexpected issues during the building process with the vcpkg manifests mode, and those could only be solved by the community involvement.)
    * Install MSYS2 (mingw subsystem of MSYS2, more stable with the vcpkg manifests mode) to build software for native windows environments from the link https://www.msys2.org/ and follow the instruction in this post. (https://github.com/microsoft/vcpkg/blob/master/docs/users/mingw.md#How-to-avoid-mixing-different-installations)

2. Clone, install, and build vcpkg as a submodule to an existing application project (official recommendations).
    * Clone the repo: git clone https://github.com/Microsoft/vcpkg.git
    * Run the bootstrap script to build vcpkg: ./vcpkg/bootstrap-vcpkg.bat (./vcpkg/bootstrap-vcpkg.sh)

3.a Check, search, install, and remove libraries for the application project through classic vcpkg methods
    * vcpkg list
    * vcpkg search [search term]
    * vcpkg install [packages to install]
    * vcpkg remove [packages to uninstall] (--recurse)  # --recurse is an useful optional parameter for libraries having many submodule.

3.b Use the vcpkg manifests mode to control the version of packages that will be installed in the project (demonstrated in this test_project).
    * Create a vcpkg.json with specified dependencies version requirements.

4. Reference and use the installed libraries with CMake and MinGW.
    * Reference and use the installed library through the find_package() and target_link_libraries() commands in the CMakeLists.txt files under the application project.
    * Configuration for generating the Makefile: 
      cmake [build directory] -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic" or "x64-mingw-static" (accroding to the selected compiler and the building mode.)
    * For the MSVC compiler version:
      cmake [build directory] -G "Visual Studio 17" -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET="x64-windows" or "x64-windows-static"
    * Build and install the project:
      cmake --build . --target install


Reference
https://vcpkg.io/en/getting-started.html