cmake_minimum_required(VERSION 3.22)

project (${PROJECT_NAME} VERSION 0.1.0)

juce_add_gui_app(${PROJECT_NAME}
    COMPANY_NAME ${COMPANY_NAME}
    PRODUCT_NAME ${PROJECT_NAME}
)

target_sources(${PROJECT_NAME}
    PRIVATE
        source/Main.cpp
        source/MainComponent.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        juce::juce_gui_extra
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
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>"
)

if (MSVC)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
)
endif()

