# Auto-Tempo-Detection 🎶 👋

Welcome to the Auto-Tempo-Detection project! This repository supports both a standalone application and VST3 plugin for automatic tempo detection in audio. 🎧

# Dependencies

Before you start, make sure you have the following installed:

- CMake 
- Git
- C++ Compiler
- (optional : additional dependencies you might need for VST3 Plugin) [VST3 SDK](https://www.steinberg.net/developers/) 


# Instructions

To use this project, follow these steps:

#### Clone the repository
```
git clone https://github.com/Audio-Project-Workgroup/Auto-Tempo-Detection.git
```

#### Download submodules
```
cd Auto-Tempo-Detection
git submodule init
git submodule update --recursive
```
*in case the above commands have no effect, consider downloading manually the repositories into the `libs` directory.*
 
#### Install dependencies 

- BTrack
BTrack is located in the `libs` directory. Follow the [instructions](https://github.com/ENOCKMOSETI/BTrack#requirements) to install BTrack's dependencies.

#### Set the flags for conditional compiling

The flags currently supported are the following:

- BUILD_PLUGIN 		(Build the plugin. Defaut value : ON)
- BUILD_APP 		(Build the application. Defaut value : ON)
- BUILD_TESTS 		(Build tests for the plugin and the application. Defaut value : ON)
- BUILD_PLUGIN_HOST (Build Juce's AudioPluginHost application to host the vst3 plugin. It is built only if BUILD_PLUGIN enabled. Defaut value : ON)


#### Build the Project
```
cmake -S . -B build
cmake --build build
```

Once the build is complete, you will find the :

- VST3 Plugin file within `build/plugin/Auto-Tempo-Detection_Plugin_artefacts/Debug/VST3/` directory (if `BUILD_PLUGIN` enabled).
- Standalone Application executable within `build/app/Auto-Tempo-Detection_artefacts/Debug/` directory (if `BUILD_APP` enabled).
- AudioPluginHost application within `build/libs/juce/extras/AudioPluginHost/AudioPluginHost_artefacts/` directory (if both `BUILD_PLUGIN` and `BUILD_PLUGIN_HOST` are enabled).

#### Hints 

*As for the VST3 Plugin, you can load the VST3 plugin into a supported host application, such as a Digital Audio Workstation (DAW), to use it within a music production environment. Make sure to place the built VST3 plugin file in a plugin directory that is recognized by your DAW.Otherwise, a more convienient solution would be to use the `AudioPluginHost` instead.*

*As for the Standalone Application, you can run the standalone application directly from the terminal.*

#### Run the tests
If `BUILD_TESTS` is enabled during configuration, you may find the test executable(s) within build directory.
- To apply the tests for `Auto-Tempo-Detection`, run the `AutoTempoDetectionTests` somewhere within `build/test/` (i.e. `build\test\Debug\AutoTempoDetectionTests.exe` for Windows)
- To apply the tests for `BTrack`, run the binary from somewhere within `build/libs/BTrack/tests/`.