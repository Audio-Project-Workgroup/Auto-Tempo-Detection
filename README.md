# Cadence

Cadence is a C++ project for **automatic tempo detection**.
It currently provides a VST3 plugin and maintains the structure for a future standalone application. 🎧

[![Version](https://img.shields.io/badge/version-0.0.1-blue)](https://github.com/Audio-Project-Workgroup/Auto-Tempo-Detection)
[![License](https://img.shields.io/badge/license-MIT-yellow)](https://github.com/Audio-Project-Workgroup/Auto-Tempo-Detection)
[![Year](https://img.shields.io/badge/year-2025-brightgreen)](https://github.com/Audio-Project-Workgroup/Auto-Tempo-Detection)
[![CI](https://github.com/Audio-Project-Workgroup/Auto-Tempo-Detection/actions/workflows/ci.yml/badge.svg)](https://github.com/Audio-Project-Workgroup/Auto-Tempo-Detection/actions/workflows/ci.yml)

# Dependencies

Before building the project, make sure you have the following installed:

- CMake 
- Git
- C++ Compiler
- (optional : additional dependencies you might need for VST3 Plugin) [VST3 SDK](https://www.steinberg.net/developers/) 

All remaining dependencies are downloaded automatically during configuration using **CPM**.

# Getting Started

#### Clone the repository
```
git clone https://github.com/Audio-Project-Workgroup/Auto-Tempo-Detection.git
```

#### Download submodules
```
cd Auto-Tempo-Detection
git submodule update --init --recursive
```

This will directly download the following [BTrack](https://github.com/ENOCKMOSETI/BTrack) and [BeatNet](https://github.com/pasquale90/BeatNet/blob/main/onnx/README.md) projects within the `libs` directory.

#### Build Configuration

The following CMake options are supported:

| Option           | Description                               | Default |
| ---------------- | ----------------------------------------- | ------- |
| BUILD_PLUGIN | Build the plugin. | `ON` |
| BUILD_APP | Build the application. | `ON` |
| BUILD_TESTS | Build tests for the plugin and the application. | `ON` |
| BUILD_PLUGIN_HOST | Build Juce's AudioPluginHost application to host the vst3 plugin. It is built only if `BUILD_PLUGIN` enabled. | `ON` |

#### Build the Project
```
cmake -S . -B build
cmake --build build
```

Once the build is complete, you will find the :

- VST3 Plugin file within `build/plugin/Auto-Tempo-Detection_Plugin_artefacts/Debug/VST3/` directory (if `BUILD_PLUGIN` enabled).
- Standalone Application executable within `build/app/Auto-Tempo-Detection_artefacts/Debug/` directory (if `BUILD_APP` enabled).
- AudioPluginHost application within `build/libs/juce/extras/AudioPluginHost/AudioPluginHost_artefacts/` directory (if both `BUILD_PLUGIN` and `BUILD_PLUGIN_HOST` are enabled).

#### Usage Hints 

*As for the VST3 Plugin, you can load the VST3 plugin into a supported host application, such as a Digital Audio Workstation (DAW), to use it within a music production environment. Make sure to place the built VST3 plugin file in a plugin directory that is recognized by your DAW. Otherwise, a more convenient solution would be to use the `AudioPluginHost` instead.*

*As for the Standalone Application, you can run the standalone application directly from the terminal.*

#### Running Tests

If `BUILD_TESTS` is enabled during configuration, you may find the test executable(s) within the build directory.
- To apply the tests for `Cadence`, run the `CadenceTests` somewhere within `build/test/` (i.e. `build\test\Debug\CadenceTests.exe` for Windows)
- To apply the tests for `BTrack`, run the binary from somewhere within `build/libs/BTrack/tests/`.