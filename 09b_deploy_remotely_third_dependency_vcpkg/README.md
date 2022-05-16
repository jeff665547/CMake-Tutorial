To import a custom library/module into the vcpkg dependency management system, we must create and use the self-made registry to tell the vcpkg where to find the custom library/module with the specified version. 
* In vcpkg, port isn't necessarily a library/module package. Some modularised libraries have many port scripts.
1. Clone, install, and build the vcpkg as a submodule to an existing application project.
2. Create a custom registries (e.g. vcpkg-ports) folder containing ports version of our custom library/module with the following information:
  a. protfile.cmake (@vcpkg-ports/ports/<library/module>)
    -- This file includes how to build and install our custom library/module via vcpkg framework.
  b. vcpkg.json (@vcpkg-ports/ports/<library/module>)
    -- This file includes the dependencies and their version information used in our custom library/module.
  c. <library/module>.json (@vcpkg-ports/versions/<X->)
    -- This file includes all the available versions of our custom library/module and the corresponding git-tree information referring to a. and b.
  d. baseline.json (@vcpkg-ports/versions)
    -- This file includes the latest version information of each library/module lying in this custom registry (vcpkg-ports). 
  e. (optional) <patch file>.patch 
    -- This file includes the patching information used to fix some bugs or adapt for different CMake configuration scenarios.
3. Commit and push the current information in the custom registry (vcpkg-ports) to the remote repository.
4. Use the custom library/module via the manifest mode (through the following files) of the vcpkg package management system:
  a. vcpkg-configuration.json
    -- This file is used to tell vcpkg where to find the registry information of our custom library/module.
  b. vcpkg.json
    -- This file specifies the dependencies and their version information used in our current downstream project.
5. Download the source code of the specified dependency and configure the downstream application project with the CMake command.
  e.g. cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH="../install" -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic"
6. Build and Install the application project.
  e.g. cmake --build . --target install

Ref
1. The Full Process (Registry): https://devblogs.microsoft.com/cppblog/registries-bring-your-own-libraries-to-vcpkg/
2. Creating Registries: https://github.com/microsoft/vcpkg/blob/master/docs/maintainers/registries.md
3. Using Registries: https://vcpkg.io/en/docs/users/registries.html
4. versions information: https://vcpkg.io/en/docs/users/versioning.implementation-details.html