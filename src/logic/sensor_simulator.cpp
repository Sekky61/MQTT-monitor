#include "message_system.hpp"

#include <iostream>

#include <string>
#include <unordered_map>

#include <stdexcept>

#include <fstream>
#include <streambuf>

#include "sim_device.hpp"

class ConfigReader
{

    std::string config_content;
    std::stringstream buffer;

    enum Parser
    {
        Header,
        Empty,
        DeviceType,
        DeviceName,
        Topic,
        Rate,
        Param
    };

public:
    ConfigReader(std::string config_path)
    {

        std::ifstream t(config_path);
        //std::stringstream buffer;
        buffer << t.rdbuf();
        config_content = buffer.str();
    };

    std::vector<sim_device *> parse_file()
    {
        std::vector<sim_device *> devices;

        std::string line;

        Parser state = Parser::Header;

        sim_device *dev = nullptr;
        std::string name;
        std::string topic;
        int rate;

        while (std::getline(buffer, line))
        {
            switch (state)
            {
            case Parser::Header:
                if (line != "mqtt-sim-config")
                {
                    throw std::runtime_error("Parse error: bad header");
                }
                state = Parser::Empty;
                break;

            case Parser::Empty:
                if (line != "")
                {
                    throw std::runtime_error("Parse error: empty line expected");
                }
                state = Parser::DeviceType;
                break;

            case Parser::DeviceType:
                if (line == "float-device")
                {
                    dev = new float_sim_device();
                }
                else if (line == "value-set-device")
                {
                    dev = new value_set_device();
                }
                else
                {
                    throw std::runtime_error("Parse error: unknown device kind");
                }
                state = Parser::Param;
                break;

            case Parser::DeviceName:
                name = line;
                state = Parser::Topic;
                break;

            case Parser::Topic:
                if (line.substr(0, 6) == "topic ")
                {
                    topic = line.substr(6);
                    state = Parser::Rate;
                }
                else
                {
                    throw std::runtime_error("Parse error: topic<space> expected");
                }
                break;

            case Parser::Rate:
                if (line.substr(0, 5) == "rate ")
                {
                    rate = std::stoi(line.substr(5));
                    state = Parser::Kind;
                }
                else
                {
                    throw std::runtime_error("Parse error: rate<space> expected");
                }
                break;

            case Parser::Param:
                if (line == "")
                {
                    state = Parser::DeviceName;
                    break;
                }
                else
                {
                    std::vector<std::string> tokens;
                    std::string token;
                    std::istringstream tokenStream(line);
                    while (std::getline(tokenStream, token, ' '))
                    {
                        tokens.push_back(token);
                    }

                    // values muze mit libovolny pocet tokenu
                    if (tokens[0] == "values")
                    {
                        std::vector<std::string>::const_iterator second_item = tokens.begin() + 1;
                        std::vector<std::string>::const_iterator end = tokens.end();
                        std::vector<std::string> string_values(second_item, end);
                        devices.back().values = string_values;

                        state = Parser::Param;
                        continue;
                    }

                    // ostatni presne 2
                    if (tokens.size() != 2)
                    {
                        throw std::runtime_error("Parse error: key<space>value expected");
                    }

                    std::string prop_name = tokens[0];
                    std::string prop_value = tokens[1];

                    if (prop_name == "rate")
                    {
                        devices.back().rate = std::stoi(prop_value);
                    }
                    else if (prop_name == "topic")
                    {
                        devices.back().topic = prop_value;
                    }
                    else
                    {
                        devices.back().properties[prop_name] = std::stof(prop_value);
                    }

                    state = Parser::Param;
                }
                break;
            }
        }

        return devices;
    }

    std::string get_content()
    {
        return config_content;
    }

    std::stringstream &get_buffer()
    {
        return buffer;
    }
};

class SensorNetwork
{

    MessageSystem &system;

public:
    int transmitting;
    std::string config_file_path;
    std::vector<sim_device> devices;

    SensorNetwork(MessageSystem &sys);

    int get_devices(std::string);
    int start_transmitting();
};

SensorNetwork::SensorNetwork(MessageSystem &sys) : system(sys),
                                                   transmitting(5) {}

int SensorNetwork::get_devices(std::string file_path)
{
    ConfigReader cfg(file_path);
    devices = cfg.parse_file();

    return 0;
}

int SensorNetwork::start_transmitting()
{
    using namespace std::chrono_literals;

    if (!system.connected)
    {
        int conn = system.connect_client();
        if (conn != 0)
        {
            return 1;
        }
    }

    std::vector<int> delays;

    for (auto &dev : devices)
    {
        // Do stuff
        std::cout << "Starting transmission: " << dev.name << " with rate " << dev.rate << std::endl;

        for (auto &prop : dev.properties)
        {
            std::cout << "\t" << prop.first << " : " << prop.second << "\n";
        }
    }

    int clock = 0; // mby clock = 1

    while (true)
    {
        std::this_thread::sleep_for(1000ms);
        std::cerr << "Clock " << clock << "\n";

        for (auto &dev : devices)
        {
            if (clock % dev.rate == 0)
            {
                std::string msg = dev.generate_msg();
                system.send_message(dev.topic, msg.data(), msg.size());
                std::cerr << "Clock " << clock << ": Sent " << dev.topic << " - " << msg << "\n";
            }
        }

        clock++;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    MessageSystem sys("Tester", "tcp://localhost:1888");

    SensorNetwork network(sys);

    int ret = network.get_devices("test_config.cfg");
    if (ret)
    {
        return ret;
    }

    for (auto &dev : network.devices)
    {
        // Do stuff
        std::cout << "\nDevice: " << dev.name << std::endl;
        for (auto &prop : dev.properties)
        {
            std::cout << "\t" << prop.first << " : " << prop.second << "\n";
        }
    }

    network.start_transmitting();

    return 0;
}