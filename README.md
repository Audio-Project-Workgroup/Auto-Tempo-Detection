# Auto-Tempo-Detection 🎶 👋

Welcome to the Auto-Tempo-Detection project! This repository supports both a standalone application and VST3 plugin for automatic tempo detection in audio. 🎧

# Dependencies

Before you start, make sure you have the following installed:

- CMake (for building the project)
- Git (for version control)
- GNU C++ Compiler (for Linux)

Additional Dependencies for VST3 Plugin (if applicable)

- VST3 SDK (if you plan on building the VST3 plugin)

### Instructions

To use this project, follow these steps:

#### Clone the repository
```
git clone https://github.com/Audio-Project-Workgroup/Auto-Tempo-Detection.git
cd Auto-Tempo-Detection
```

#### Build the Project
```
cmake -S . -B build
cmake --build build
```

Once the build is complete, you will find the following output:

- VST3 Plugin (for supported hosts like DAWs)
    - Linux:`build/plugin/Auto-Tempo-Detection_Plugin_artefacts/Debug/VST3/AudioProjectWorkgroup.vst3`
    - Windows : `...`
    - Mac : `...`
- Standalone Application (for running the app directly)
    - Linux:`build/app/Auto-Tempo-Detection_artefacts/Debug/Auto-Tempo-Detection`
    - Windows : `...`
    - Mac : `...`

*As for the VST3 Plugin, you can load the VST3 plugin into a supported host application, such as a Digital Audio Workstation (DAW), to use it within a music production environment. Make sure to place the built VST3 plugin file in a plugin directory that is recognized by your DAW.*

*As for the Standalone Application, you can run the standalone application directly from the terminal.*

#### Run the tests

For Linux:
```
./build/test/AutoTempoDetectionTest
```

For Windows:
```
...
```
For macOS:
```
...
```