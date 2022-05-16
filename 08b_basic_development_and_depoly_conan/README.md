0. Prerequisites
    * OS: Windows
    * OS: macOS
    * OS: Linux and other OS.
    * Python >= 3.5 with pip3 package manager.
    * g++: e.g. mingw64
    * Command Prompt (cmd) is required.

1. Create, enter a virtual environment (venv) and install the Conan.
    * pip install virtualenvwrapper-win
    * mkvirtualenv venv
    * pip install conan
    * (optional) deactivate                --> Exit the venv.
    * (optional) workon                    --> List the available virtual environments.
    * (optional) workon/rmvirtualenv venv  --> Activate/Remove venv.

2. Create the conanfile.txt with the integration generator and the specified dependencies with their versions under this project's directory.

3. Create a profile to specify the compiler and other environment settings we used.
    * e.g. mingw64 @ C:/Users/<UserName>/.conan/profiles

4. Go to the build directory under our project, build and install the required dependencies from the source and generate the information for integrating into the CMake building process.
    * conan install .. --build=missing --profile=mingw64  or  conan install .. --build=missing -pr=mingw64
    * (optional) conan profile list            --> List existing available profiles.
    * (optional) conan profile show mingw64    --> Show the content of the mingw64 profile.

5. CMake configuration and build the project and tests.


Reference
https://docs.conan.io/en/latest/getting_started.html#getting-started-other-configurations
