cmake_minimum_required(VERSION 3.22)

set(COMPANY_NAME AudioProjectWorkgroup)
set(PROJECT_NAME Auto-Tempo-Detection)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Options to build the app and/or the vst3 are enabled by default
option(BUILD_PLUGIN "Build the plugin" ON)
option(BUILD_APP "Build the application" ON)
option(BUILD_TESTS "Build tests for the plugin and the application" ON)

include(cmake/cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 8.0.6
    VERSION 8.0.6
    SOURCE_DIR ${LIB_DIR}/juce
)

CPMAddPackage(
    NAME GOOGLETEST
    GITHUB_REPOSITORY google/googletest
    VERSION 1.13.0
    SOURCE_DIR ${LIB_DIR}/googletest
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

enable_testing()

if (MSVC)
    # add_compile_options()
    # /WX treats juce warnings as errors when building the tests
    # /Wall treats juce warnings as errors when building the vst/app.
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(BUILD_APP)
    add_subdirectory(app)
endif()
if(BUILD_PLUGIN)
    add_subdirectory(plugin)
endif()
if(BUILD_TESTS)
    add_subdirectory(test)
endif()

add_subdirectory(${LIB_DIR}/BTrack)
