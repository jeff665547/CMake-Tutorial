cmake_minimum_required(VERSION 3.15)

# ---------------------------------------------------------------------------------------
# Add a header-only library target.
# ---------------------------------------------------------------------------------------
add_library(status INTERFACE)

# ---------------------------------------------------------------------------------------
# Specify the directories used for using executable.
# --------------------------------------------------------------------------------------
target_include_directories(status INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(status INTERFACE cxx_std_11)