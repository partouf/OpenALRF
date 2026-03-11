# OpenALRF

A library meant as a foundation to build your own robot code on top of.

Currently under development as part of [AudacityRover](https://github.com/partouf/AudacityRover)

## Building

```bash
cmake -B build
cmake --build build
```

Ready to use implementations:
* SensorBus pattern

Base for:
* World orientation
* Command Queue
* Communication
* Piloting
* Sensors
* Cameras
* Image Processing
