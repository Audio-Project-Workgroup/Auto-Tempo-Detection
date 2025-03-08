#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED // https://forum.juce.com/t/error-no-global-header-file-was-included/19843

#ifdef BUILD_PLUGIN_TESTS
  #include "pluginTests.h"
#endif
#ifdef BUILD_APP_TESTS
  #include "applicationTests.h"
#endif

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}