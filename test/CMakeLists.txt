cmake_minimum_required(VERSION 3.22)

project (AutoTempoDetectionTests)

enable_testing()

set(TEST_LIBRARIES 
    GTest::gtest_main
)

set(PUBLIC_CONDITIONAL_TEST_LIBRARIES)

add_executable(${PROJECT_NAME} 
    allTests.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${GOOGLETEST_SOURCE_DIR}/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../plugin/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../app/include
        ${JUCE_SOURCE_DIR}/modules
)

if(${BUILD_APP})
    add_definitions(-DBUILD_APP_TESTS)
    # if building app, and NOT building plugin ...
    # ... you ll need to link against juce libraries. This was done through the VST, but now this is not compiled.
    if(NOT ${BUILD_PLUGIN}) 
        list(APPEND TEST_LIBRARIES juce::juce_gui_extra)
        list(APPEND PUBLIC_CONDITIONAL_TEST_LIBRARIES juce::juce_recommended_config_flags)
        list(APPEND PUBLIC_CONDITIONAL_TEST_LIBRARIES juce::juce_recommended_lto_flags)
        list(APPEND PUBLIC_CONDITIONAL_TEST_LIBRARIES juce::juce_recommended_warning_flags)
    endif()
endif()
if(${BUILD_PLUGIN})
    add_definitions(-DBUILD_PLUGIN_TESTS)
    list(APPEND TEST_LIBRARIES atd_vst_library)
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${TEST_LIBRARIES}
    PUBLIC
        ${PUBLIC_CONDITIONAL_TEST_LIBRARIES}
)