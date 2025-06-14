cmake_minimum_required(VERSION 3.22)

set(COMPANY_NAME AudioProjectWorkgroup)
set(PROJECT_NAME Auto-Tempo-Detection)

project(${PROJECT_NAME} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Options to build the app and/or the vst3 are enabled by default
option(BUILD_PLUGIN "Build the plugin" ON)
option(BUILD_APP "Build the application" ON)
option(BUILD_TESTS "Build tests for the plugin and the application" ON)
option(BUILD_PLUGIN_HOST "Build Juce's AudioPluginHost application to host the vst3 plugin. It is built only if BUILD_PLUGIN enabled" ON)

include(cmake/cpm.cmake)

set(JUCE_DIR "${LIB_DIR}/juce")
set(GTEST_DIR "${LIB_DIR}/googletest")
if(NOT EXISTS ${JUCE_DIR}/CMakeLists.txt)
    CPMAddPackage(
        NAME JUCE
        GITHUB_REPOSITORY juce-framework/JUCE
        GIT_TAG 8.0.6
        VERSION 8.0.6
        SOURCE_DIR ${LIB_DIR}/juce
    )
else()
    add_subdirectory(${JUCE_DIR})
    message(STATUS "JUCE found locally at ${JUCE_DIR}, skipping download")
endif()
if(NOT EXISTS ${GTEST_DIR}/CMakeLists.txt)
    CPMAddPackage(
        NAME GOOGLETEST
        GITHUB_REPOSITORY google/googletest
        VERSION 1.13.0
        SOURCE_DIR ${LIB_DIR}/googletest
        OPTIONS
            "INSTALL_GTEST OFF"
            "gtest_force_shared_crt ON"
    )
else()
    add_subdirectory(${GTEST_DIR})
    message(STATUS "GTEST found locally at ${GTEST_DIR}, skipping download")
endif()

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
    if (BUILD_PLUGIN_HOST)
        add_subdirectory(${LIB_DIR}/juce/extras/AudioPluginHost)
    endif()
endif()
if(BUILD_TESTS)
    add_subdirectory(test)
endif()

add_subdirectory(${LIB_DIR}/BTrack)