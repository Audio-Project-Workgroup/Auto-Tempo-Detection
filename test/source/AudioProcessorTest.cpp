#include <gtest/gtest.h>
#include "AudioProjectWorkgroup/PluginProcessor.h"
          

namespace audio_plugin_test {

    TEST(PLUGIN, InitAudioPluginAudioProcessor){
        AudioPluginAudioProcessor processor{};
        ASSERT_FALSE(true);
    }
}