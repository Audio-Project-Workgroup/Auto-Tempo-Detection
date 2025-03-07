cmake_minimum_required(VERSION 3.22)

project (AutoTempoDetectionTests)

enable_testing()

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

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        atd_vst_library
        GTest::gtest_main
)