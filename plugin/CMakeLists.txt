cmake_minimum_required(VERSION 3.22)

project (${PROJECT_NAME}_Plugin VERSION 0.1.0)

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME ${COMPANY_NAME}
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE APWG
    PLUGIN_CODE ATDP
    FORMATS VST3
    PRODUCT_NAME ${COMPANY_NAME}
)

add_library(atd_vst_library ALIAS ${PROJECT_NAME})

juce_generate_juce_header(${PROJECT_NAME})

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        BTrack
        beatnetlib
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_sources(${PROJECT_NAME}
    PRIVATE
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        source/Display.cpp
        source/CustomLookAndFeel.cpp
        source/CustomButton.cpp
        source/tempo/beatrack.cpp
        source/tempo/beatNeTracker.cpp
        source/tempo/interface.cpp
        source/ButtonLookAndFeel.cpp
        source/BeatLedOut.cpp
)   

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

if (MSVC)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
)
endif()

# Cross-platform VST3 dependency copying based on official VST3 specification:
# https://steinbergmedia.github.io/vst3_dev_portal/pages/Technical+Documentation/Locations+Format/Plugin+Format.html
function(copy_vst3_dependencies target_name)
    # Detect architecture
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH "x86_64")
    else()
        set(ARCH "i386")  # Note --> VST3 spec uses "i386" not "i686"
    endif()
    
    # Define platform-specific variables
    if(WIN32)
        set(VST3_BUNDLE_SUFFIX ".vst3")
        # windows VST3 structure: Contents/x86_64-win/ or Contents/i386-win/
        if(ARCH STREQUAL "x86_64")
            set(VST3_CONTENTS_DIR "Contents/x86_64-win")
        else()
            set(VST3_CONTENTS_DIR "Contents/x86-win")  # 32-bit uses "x86-win" not "i386-win"
        endif()
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
        set(VST3_BUNDLE_SUFFIX ".vst3")
        # macOS VST3 structure: Contents/MacOS/
        set(VST3_CONTENTS_DIR "Contents/MacOS")
        set(LIB_EXTENSION ".dylib")
        set(LIB_PREFIX "lib")
        
        set(LIBS_AND_WEIGHTS
            "${ORT_DIR}/lib/${LIB_PREFIX}onnxruntime${LIB_EXTENSION}"
            "${SAMPLERATE_DIR}/lib/${LIB_PREFIX}samplerate${LIB_EXTENSION}"
        )
        if(ENABLE_FFTW3)
            list(APPEND LIBS_AND_WEIGHTS "${FFTW3_DIR}/lib/${LIB_PREFIX}fftw3f${LIB_EXTENSION}")
        endif()
        
    elseif(UNIX) # Linux and other Unix systems
        set(VST3_BUNDLE_SUFFIX ".vst3")
        # linux VST3 structure: Contents/x86_64-linux/ or Contents/i386-linux/
        set(VST3_CONTENTS_DIR "Contents/${ARCH}-linux")
        set(LIB_EXTENSION ".so")
        set(LIB_PREFIX "lib")
 
        file(GLOB SAMPLERATE_DLIBS 
            "${SAMPLERATE_DIR}/lib/${LIB_PREFIX}samplerate${LIB_EXTENSION}*"
            "${SAMPLERATE_DIR}/lib64/libsamplerate${LIB_EXTENSION}*")
        list(APPEND LIBS_AND_WEIGHTS ${SAMPLERATE_LIBS})
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
    
    # append the onnx model
    list(APPEND LIBS_AND_WEIGHTS "${BEATNET_ONNX_ROOTDIR}/beatnet_bda.onnx")

    set(VST3_TARGET_DIR "$<TARGET_FILE_DIR:${target_name}>/VST3/AudioProjectWorkgroup${VST3_BUNDLE_SUFFIX}/${VST3_CONTENTS_DIR}")
    
    if(LIBS_AND_WEIGHTS)
        add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${VST3_TARGET_DIR}"
            COMMENT "Precreating the installation dir of the VST3"
        )
        foreach(DEP_FILE IN LISTS LIBS_AND_WEIGHTS)
            if (EXISTS "${DEP_FILE}")
                add_custom_command(TARGET ${target_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        ${DEP_FILE}
                        "${VST3_TARGET_DIR}"
                    COMMENT "Copying ${DEP_FILE} VST3 dependency for ${CMAKE_SYSTEM_NAME} to ${VST3_CONTENTS_DIR}"
                )
            else()
                message("Unable to copy ${DEP_FILE} into ${VST3_CONTENTS_DIR}. Please copy it manually to ensure the runtime dependencies are available.")
            endif()
        endforeach()
    endif()
endfunction()

copy_vst3_dependencies(${PROJECT_NAME})