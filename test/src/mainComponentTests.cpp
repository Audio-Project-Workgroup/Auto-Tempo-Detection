#include <gtest/gtest.h>
#include "AudioProjectWorkgroup/MainComponent.h"
          
TEST(APPLICATION, InitMainComponent){
    try {
        MainComponent component();
    } catch (const std::exception& e) {
        FAIL() << "Runtime error during initialization: " << e.what();
    } catch (...) {
        FAIL() << "Unknown error during initialization";
    }
}