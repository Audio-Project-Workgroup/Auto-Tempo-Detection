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

target_sources(${PROJECT_NAME}
    PRIVATE
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        source/Display.cpp 
        source/CustomLookAndFeel.cpp
        source/CustomButton.cpp
        source/tempo/beatrack.cpp
        source/tempo/interface.cpp
        ${LIB_DIR}/BTrack/src/BTrack.cpp
        ${LIB_DIR}/BTrack/src/OnsetDetectionFunction.cpp
        ${LIB_DIR}/BTrack/libs/kiss_fft130/kiss_fft.c
)   

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include   
        ${LIB_DIR}/BTrack/src/
        ${LIB_DIR}/BTrack/libs/kiss_fft130/
        ${LIB_DIR}/BTrack/libs/libsamplerate-0.2.2-win64/include/
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        BTrack
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
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

