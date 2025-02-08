# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Auto-Tempo-Detection)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    src/main.cpp
)

# Add the executable that will be built from the main.cpp file
add_executable(auto-tempo-detection ${SOURCE_FILES})
