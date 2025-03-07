#include "src/audioProcessorTests.cpp"
#include "src/mainComponentTests.cpp"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}