CC = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -O2
LDFLAGS = -lpaho-mqtt3c -lpaho-mqtt3a -lpaho-mqttpp3

CPP_FILES = entry.cpp message_system.cpp

all: listen_all

# Object files dependencies

message_system.o: message_system.cpp message_system.hpp tree_node.hpp
entry.o: entry.cpp message_system.hpp tree_node.hpp

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

listen_all: entry.o message_system.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)


.PHONY: clean

clean:
	rm -f listen_all *.o