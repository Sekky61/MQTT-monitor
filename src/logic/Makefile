CC = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -O2
LDFLAGS = -lpaho-mqtt3a -lpaho-mqttpp3

CPP_FILES = entry.cpp message_system.cpp

all: listen_all test sim

# Object files dependencies

message_system.o: message_system.cpp message_system.hpp
sensor_simulator.o: sensor_simulator.cpp
entry.o: entry.cpp

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

sim: sensor_simulator.o message_system.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

listen_all: entry.o message_system.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)


test: test.cpp
	$(CC) -o $@ $^ -std=c++17 $(LDFLAGS)


.PHONY: clean

clean:
	rm -f listen_all test sim *.o