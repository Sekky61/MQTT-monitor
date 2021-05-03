/*! \file sensor_simulator.cpp
    \brief Simulator MQTT provozu
    
    Trida SensorNetwork vysilajici MQTT zpravy podle konfiguracniho
    souboru
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

#include "../logic/message_system.hpp"
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
                else if (line == "picture-device")
                {
                    dev = new picture_device();
                }
                else
                {
                    throw std::runtime_error("Parse error: unknown device kind");
                }
                state = Parser::DeviceName;
                break;

            case Parser::DeviceName:
                dev->set_name(line);
                state = Parser::Topic;
                break;

            case Parser::Topic:
                if (line.substr(0, 6) == "topic ")
                {
                    dev->set_topic(line.substr(6));
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
                    dev->set_rate(std::stoi(line.substr(5)));
                    state = Parser::Param;
                }
                else
                {
                    throw std::runtime_error("Parse error: rate<space> expected");
                }
                break;

            case Parser::Param:
                if (line == "")
                {
                    // konec konfigurace zarizeni
                    devices.push_back(dev);
                    dev = nullptr;
                    state = Parser::DeviceType;
                    break;
                }

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

                    // neni implementovano ve vsech zarizenich
                    dev->set_values(string_values);

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

                //todo switch idk
                if (prop_name == "max-val")
                {
                    float_sim_device *flt_dev = dynamic_cast<float_sim_device *>(dev);
                    flt_dev->set_max_val(std::stof(prop_value));
                }
                else if (prop_name == "min-val")
                {
                    float_sim_device *flt_dev = dynamic_cast<float_sim_device *>(dev);
                    flt_dev->set_min_val(std::stof(prop_value));
                }
                else if (prop_name == "max-delta")
                {
                    float_sim_device *flt_dev = dynamic_cast<float_sim_device *>(dev);
                    flt_dev->set_max_delta(std::stof(prop_value));
                }
                else if (prop_name == "change-chance")
                {
                    value_set_device *set_dev = dynamic_cast<value_set_device *>(dev);
                    set_dev->set_change_chance(std::stof(prop_value));
                }
                else
                {
                    throw std::runtime_error("Parse error: unknown parameter");
                }

                state = Parser::Param;
                break;
            }
        }

        if (dev != nullptr)
        {
            devices.push_back(dev);
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
    std::vector<sim_device *> devices;

    SensorNetwork(MessageSystem &sys) : system(sys),
                                        transmitting(5)
    {
        if (!system.connected)
        {
            int conn = system.connect_client();
            if (conn != 0)
            {
                throw conn; //todo
            }
        }
    };

    int get_devices(std::string);
    int start_transmitting();
    void sub_to_all_devices();
    sim_device *get_device_by_topic(std::string topic);
};

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

    for (auto *dev : devices)
    {
        // Do stuff
        std::cout << "Starting transmission: " << dev->get_name() << " with rate " << dev->get_rate() << std::endl;
    }

    int clock = 0; // mby clock = 1

    while (true)
    {
        std::this_thread::sleep_for(1000ms);
        std::cerr << "Clk" << clock << "\n";

        for (auto *dev : devices)
        {
            if (clock % dev->get_rate() == 0)
            {
                std::string msg = dev->generate_msg();
                system.send_message(dev->get_topic(), msg.data(), msg.size());
            }
        }

        clock++;
    }

    return 0;
}

void SensorNetwork::sub_to_all_devices()
{
    for (auto *dev : devices)
    {
        system.client.subscribe(dev->get_topic(), 1);
    }
}

sim_device *SensorNetwork::get_device_by_topic(std::string topic)
{
    auto it = std::find_if(devices.begin(), devices.end(), [&](auto *s) { return s->get_topic() == topic; });
    if (it == devices.end())
    {
        return nullptr;
    }
    else
    {
        return *it;
    }
}

int main(int argc, char *argv[])
{
    // seeding rand
    srand(static_cast<unsigned>(time(0)));

    if (argc != 3)
    {
        std::cerr << "Usage: ./sim address config_file\n";
        return 1;
    }

    std::string server_address = argv[1];
    std::string config_file = argv[2];

    MessageSystem sys("Tester", server_address);

    SensorNetwork network(sys);

    int ret = network.get_devices(config_file);
    if (ret)
    {
        return ret;
    }

    network.sub_to_all_devices();

    sys.client.set_message_callback([&network](const mqtt::const_message_ptr message) {
        auto topic = message->get_topic();
        auto msg = message->get_payload();
        std::cerr
            << "Callback: " << topic
            << " : " << msg.size() << " B\n";
        sim_device *dev = network.get_device_by_topic(topic);
        if (dev)
        {
            dev->set_value(msg);
        }
    });

    network.start_transmitting();

    return 0;
}