Fix the local bug and experimentally distributed -- Patching Mechanism.
* 1. Make sure the specified library/module is updated to the latest.
* 2. Go to the downloaded source code directory of the specified library/module: 
    <directory to vcpkg>\vcpkg\buildtrees\<library/module>\src\<specified version>
* 3. Use the git system to create the patch file: 
    git init . -> git add . -> git commit -m "Initial commit message."
* 4. Directly modify the code for fixing the bug or adding an experimental feature for the customed library/module.
* 5. Save the patch result from the git diff output into the ports/<library/module> directory:
    e.g. For Windows PowerShell: git diff --ignore-space-at-eol | out-file -enc ascii ../../../../../vcpkg-registries/ports/maths/disable-the-example-executable.patch
    e.g. For UNIX Shell: git diff --ignore-space-at-eol > ../../../../../vcpkg-registries/ports/maths/disable-the-example-executable.patch
* 6. Specify and apply the patch file in the portfile.cmake under the ports/<library/module> directory in the registry.
* 7. (Optional) Clear the previous building cache of vcpkg ([project]/build, vcpkg/buildtrees, vcpkg/downloads, vcpkg/packages, WIN: User/AppData/Local/vcpkg, UNIX: ~/.cache/vcpkg).
* 8. Build the application project with the -DVCPKG_OVERLAY_PORTS option at the CMake configuration:
    e.g. cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH="../install" -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic" -DVCPKG_OVERLAY_PORTS="../../vcpkg-registries/ports/maths"
* 9. Make sure the updated results behaves as expected and the following message shows during the CMake configuration process.
    -- Using cached <host>-<library/module>-<version>.tar.gz.
    -- Extracting source <path to the cached file>
    -- Applying patch <pathc filename>
                  .
                  .
                  .
                  .
                  .
    -- Using source at <path to the source under the buildtrees directory>
    -- Configuring <vcpkg target triplet>
* 10. Use the patching mechanism or directly add the change to the specifed library/module.
* 11. Update, commit the following information and publish the changes via a pull request (if using the patching mechanism):
    a. Add or update the "port-version" field in the vcpkg.json (@ports/<library/module>)
    b. Update the baseline.json (@versions)
    c. Add the new patch version to the <library/module>.json (@versions/<X->) (git rev-parse HEAD:ports/maths after git commit the above changes.)

* 12. Download and use the patched library/module in the downstream application.
    a. Update the "baseline" field to the above commit SHA in the vcpkg-configuration and directly specify the patch version in the "dependencies" -> "version>=" in the vcpkg.json.