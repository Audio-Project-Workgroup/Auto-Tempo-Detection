cmake_minimum_required(VERSION 3.22)

project (CadenceTests)

enable_testing()

set(TEST_LIBRARIES 
    GTest::gtest_main
    BTrack
    beatnetlib
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

# copy beatnet dependencies
function(copy_beatnet_dependencies_to_executable_dir target_name)

    if(WIN32)
        set(LIB_EXTENSION ".dll")
        set(LIB_PREFIX "")

        set(LIBS_AND_WEIGHTS
            "${ORT_DIR}/lib/onnxruntime${LIB_EXTENSION}"
            "${SAMPLERATE_DIR}/bin/samplerate${LIB_EXTENSION}"
        )
        if(ENABLE_FFTW3)
            list(APPEND LIBS_AND_WEIGHTS "${FFTW3_DIR}/libfftw3f-3${LIB_EXTENSION}")
        endif()

    elseif(APPLE)
        set(LIB_EXTENSION ".dylib")
        set(LIB_PREFIX "lib")

        set(LIBS_AND_WEIGHTS
            "${ORT_DIR}/lib/${LIB_PREFIX}onnxruntime${LIB_EXTENSION}"
            "${SAMPLERATE_DIR}/lib/${LIB_PREFIX}samplerate${LIB_EXTENSION}"
        )
        if(ENABLE_FFTW3)
            list(APPEND LIBS_AND_WEIGHTS "${FFTW3_DIR}/lib/${LIB_PREFIX}fftw3f${LIB_EXTENSION}")
        endif()

    elseif(UNIX)
        set(LIB_EXTENSION ".so")
        set(LIB_PREFIX "lib")

        file(GLOB SAMPLERATE_DLIBS 
            "${SAMPLERATE_DIR}/lib/${LIB_PREFIX}samplerate${LIB_EXTENSION}*"
            "${SAMPLERATE_DIR}/lib64/${LIB_PREFIX}samplerate${LIB_EXTENSION}*")
        set(LIBS_AND_WEIGHTS
            "${ORT_DIR}/lib/${LIB_PREFIX}onnxruntime${LIB_EXTENSION}"
            ${SAMPLERATE_DLIBS}
        )
        if(ENABLE_FFTW3)
            file(GLOB FFTW3_DLIBS 
                "${FFTW3_DIR}/lib/${LIB_PREFIX}fftw3f${LIB_EXTENSION}*"
                "${FFTW3_DIR}/lib64/${LIB_PREFIX}fftw3f${LIB_EXTENSION}*")
            list(APPEND LIBS_AND_WEIGHTS ${FFTW3_DLIBS})
        endif()
    endif()
    
    list(APPEND LIBS_AND_WEIGHTS "${BEATNET_ONNX_ROOTDIR}/beatnet_bda.onnx")

    foreach(DEP_FILE IN LISTS LIBS_AND_WEIGHTS)
        if (EXISTS "${DEP_FILE}")
            add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DEP_FILE}"
                    $<TARGET_FILE_DIR:${target_name}>
                COMMENT "Copying ${DEP_FILE} for ${target_name} to test installation dir."
            )
        else()
            message(WARNING "Failed to copy ${DEP_FILE} into the directory where the test executable resides. Please copy it manually to ensure the runtime dependencies are available.")
        endif()
    endforeach()

endfunction()

copy_beatnet_dependencies_to_executable_dir(${PROJECT_NAME})
