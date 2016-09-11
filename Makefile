# Project: OpenALRF

OBJ_COMMON = Common/Timing.o
OBJ_SYSTEM = System/System.o System/SystemLinux.o
OBJ_COMM = Communication/Communication.o
OBJ_COMMAND = Command/CommandQueue.o
OBJ_SENSORS = Sensors/Sensors.o Sensors/ProxySensor.o
OBJ_SENSORBUS = Communication/SensorBus.o Communication/SensorBusListener.o
OBJ_PILOT = Pilot/RemotePilot.o
OBJ_CAMERA = Camera/MainCamera.o
OBJ_IMAGEPROCESSING = ImageProcessing/Software.o
OBJ_ASTARMAPNODE = World/AStarMapNode.o
OBJ_WORLDMAP = World/Map.o

OBJ = $(OBJ_COMMON) $(OBJ_SYSTEM) $(OBJ_COMM) $(OBJ_COMMAND) $(OBJ_SENSORS) $(OBJ_SENSORBUS) $(OBJ_PILOT) $(OBJ_CAMERA) $(OBJ_IMAGEPROCESSING) $(OBJ_ASTARMAPNODE) $(OBJ_WORLDMAP)
LINKOBJ = $(OBJ)
LIBS = 
BIN  = libOpenALRF.a
CXXINCS = 
CXXFLAGS = $(CXXINCS) -g -std=c++11 -fexceptions -O2
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean:
	${RM} $(LINKOBJ) $(BIN)

$(BIN): $(LINKOBJ)
	ar r $(BIN) $(LINKOBJ)
	ranlib $(BIN)

System/System.o: System/System.cpp
	$(CXX) -c System/System.cpp -o System/System.o $(CXXFLAGS)

System/SystemLinux.o: System/SystemLinux.cpp
	$(CXX) -c System/SystemLinux.cpp -o System/SystemLinux.o $(CXXFLAGS)

Sensors/Sensors.o: Sensors/Sensors.cpp
	$(CXX) -c Sensors/Sensors.cpp -o Sensors/Sensors.o $(CXXFLAGS)

Pilot/RemotePilot.o: Pilot/RemotePilot.cpp
	$(CXX) -c Pilot/RemotePilot.cpp -o Pilot/RemotePilot.o $(CXXFLAGS)

Communication/Communication.o: Communication/Communication.cpp
	$(CXX) -c Communication/Communication.cpp -o Communication/Communication.o $(CXXFLAGS)

Communication/SensorBus.o: Communication/SensorBus.cpp
	$(CXX) -c Communication/SensorBus.cpp -o Communication/SensorBus.o $(CXXFLAGS)

Communication/SensorBusListener.o: Communication/SensorBusListener.cpp
	$(CXX) -c Communication/SensorBusListener.cpp -o Communication/SensorBusListener.o $(CXXFLAGS)

Sensors/ProxySensor.o: Sensors/ProxySensor.cpp
	$(CXX) -c Sensors/ProxySensor.cpp -o Sensors/ProxySensor.o $(CXXFLAGS)

Common/Timing.o: Common/Timing.cpp
	$(CXX) -c Common/Timing.cpp -o Common/Timing.o $(CXXFLAGS)

Command/CommandQueue.o: Command/CommandQueue.cpp
	$(CXX) -c Command/CommandQueue.cpp -o Command/CommandQueue.o $(CXXFLAGS)

Camera/MainCamera.o: Camera/MainCamera.cpp
	$(CXX) -c Camera/MainCamera.cpp -o Camera/MainCamera.o $(CXXFLAGS)

ImageProcessing/Software.o: ImageProcessing/Software.cpp
	$(CXX) -c ImageProcessing/Software.cpp -o ImageProcessing/Software.o $(CXXFLAGS)

World/AStarMapNode.o: World/AStarMapNode.cpp
	$(CXX) -c World/AStarMapNode.cpp -o World/AStarMapNode.o $(CXXFLAGS)

World/Map.o: World/Map.cpp
	$(CXX) -c World/Map.cpp -o World/Map.o $(CXXFLAGS)
