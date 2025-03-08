# Auto-Tempo-Detection 🎶 👋

Welcome to the Auto-Tempo-Detection project! This repository supports both a standalone application and VST3 plugin for automatic tempo detection in audio. 🎧

# Dependencies

Before you start, make sure you have the following installed:

- CMake 
- Git
- C++ Compiler

Additional Dependencies for VST3 Plugin

- VST3 SDK (if you plan on building the VST3 plugin)

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
#### Install dependencies 

- BTrack
BTrack is located in the `libs` directory. Follow the [instructions](https://github.com/ENOCKMOSETI/BTrack#requirements) to install BTrack's dependencies.

#### Build the Project
```
cmake -S . -B build
cmake --build build
```

Once the build is complete, you will find the :

- VST3 Plugin file within `build/plugin/Auto-Tempo-Detection_Plugin_artefacts/Debug/VST3/` directory.
- Standalone Application executable within `build/app/Auto-Tempo-Detection_artefacts/Debug/` directory.

#### Hints 

*As for the VST3 Plugin, you can load the VST3 plugin into a supported host application, such as a Digital Audio Workstation (DAW), to use it within a music production environment. Make sure to place the built VST3 plugin file in a plugin directory that is recognized by your DAW.*

*As for the Standalone Application, you can run the standalone application directly from the terminal.*

#### Run the tests
Find the test executable within build directory.
- To apply the tests for `Auto-Tempo-Detection`, run the `AutoTempoDetectionTests` somewhere within `build/test/` (i.e. `build\test\Debug\AutoTempoDetectionTests.exe` for Windows)
- To apply the tests for `BTrack`, run the binary somewhere within `build/libs/BTrack/tests/`.