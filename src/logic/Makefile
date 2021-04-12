all: mock_publish listen_all test

mock_publish: mock_publish.cpp
	g++ -std=c++17 mock_publish.cpp -o mock_publish -lpaho-mqtt3a -lpaho-mqttpp3

listen_all: entry.cpp
	g++ -std=c++17 entry.cpp -o listen_all -lpaho-mqtt3a -lpaho-mqttpp3

test: test.cpp
	g++ -std=c++17 test.cpp -o test -lpaho-mqtt3a -lpaho-mqttpp3

clean:
	rm test listen_all mock_publish