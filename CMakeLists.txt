cmake_minimum_required(VERSION 3.10)
project(OpenALRF LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(OpenALRF STATIC
   Common/Timing.cpp
   System/System.cpp
   System/SystemLinux.cpp
   Communication/Communication.cpp
   Communication/SensorBus.cpp
   Communication/SensorBusListener.cpp
   Command/CommandQueue.cpp
   Sensors/Sensors.cpp
   Sensors/ProxySensor.cpp
   Pilot/RemotePilot.cpp
   Camera/MainCamera.cpp
   ImageProcessing/Software.cpp
   World/AStarMapNode.cpp
   World/Map.cpp
)

target_include_directories(OpenALRF PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(OpenALRF PRIVATE -fexceptions)
