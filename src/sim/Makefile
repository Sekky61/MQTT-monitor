CC = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -O2
LDFLAGS = -lpaho-mqtt3a -lpaho-mqttpp3

all: mqttsim

# Object files dependencies

../logic/message_system.o: ../logic/message_system.cpp ../logic/message_system.hpp
sensor_simulator.o: sensor_simulator.cpp sim_device.hpp

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

../logic/message_system.o: ../logic/message_system.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

mqttsim: sensor_simulator.o ../logic/message_system.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f mqttsim *.o