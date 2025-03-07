#include <gtest/gtest.h>
// #define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED // https://forum.juce.com/t/error-no-global-header-file-was-included/19843
#include "AudioProjectWorkgroup/MainComponent.h"
          

namespace audio_app_test {

    TEST(APPLICATION, InitMainComponent){
        try {
            MainComponent component();
        } catch (const std::exception& e) {
            FAIL() << "Runtime error during initialization: " << e.what();
        } catch (...) {
            FAIL() << "Unknown error during initialization";
        }
    }
}