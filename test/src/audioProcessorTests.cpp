#include <gtest/gtest.h>
#include "AudioProjectWorkgroup/PluginProcessor.h"
          
TEST(PLUGIN, InitAudioPluginAudioProcessor){
    try {
        AudioPluginAudioProcessor processor{};
    } catch (const std::exception& e) {
        FAIL() << "Runtime error during initialization: " << e.what();
    } catch (...) {
        FAIL() << "Unknown error during initialization";
    }
}