CC = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -O2
LDFLAGS = -lpaho-mqtt3a -lpaho-mqttpp3

CPP_FILES = entry.cpp message_system.cpp

all: listen_all test

# Object files dependencies

message_system.o: message_system.cpp message_system.hpp
entry.o: entry.cpp

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

listen_all: entry.o message_system.o
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test: test.cpp
	$(CC) -o $@ $^ -std=c++17 $(LDFLAGS)

.PHONY: clean

clean:
	rm -f test listen_all message_system.o entry.o