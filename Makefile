# Makefile
#
# xmajer21
# xpoucp01
#
# vysledky prekladu jsou ukladany do slozek build a doc (vyjma archivu)

# make					vytvoreni exploreru, simulace, dokumentace
# make mqttexplorer		vytvoreni exploreru
# make run				vytvoreni a spusteni exploreru
# make doxygen			vytvoreni dokumentace
# make pack 			vytvoreni archivu pro odevzdani
# make clean			odstraneni produktu prekladu

CC = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -O2
LDFLAGS = -lpaho-mqtt3c -lpaho-mqtt3a -lpaho-mqttpp3

AUTHOR_1 = xmajer21
AUTHOR_2 = xpoucp01

BUILD_DIR = build
ZIP_NAME = 1-$(AUTHOR_1)-$(AUTHOR_2).zip
FILES_TO_ZIP = Makefile src examples README.txt

all: mqttexplorer mqttsim doxygen

# MAKE BUILD DIR

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# EXPLORER

mqttexplorer: | $(BUILD_DIR)
	cd $(BUILD_DIR) && echo "I'm in $(BUILD_DIR)" && \
	qmake ../src/gui/MQTTexplorer.pro; make

# SIMULATOR

mqttsim: $(BUILD_DIR)/mqttsim | $(BUILD_DIR)

$(BUILD_DIR)/message_system.o: src/logic/message_system.cpp src/logic/message_system.hpp | $(BUILD_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/sensor_simulator.o: src/sim/sensor_simulator.cpp src/sim/sim_device.hpp | $(BUILD_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/mqttsim: $(BUILD_DIR)/sensor_simulator.o $(BUILD_DIR)/message_system.o | $(BUILD_DIR)
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# DOCS

doxygen:
	doxygen src/Doxyfile

# PHONIES
.PHONY: clean pack run

run: mqttexplorer
	./build/MQTTexplorer

pack:
	zip -r $(ZIP_NAME) $(FILES_TO_ZIP)

clean:
	rm -rf $(BUILD_DIR) doc $(ZIP_NAME)