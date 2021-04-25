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

                    // throws if actual object is not derived class
                    value_set_device *set_dev = dynamic_cast<value_set_device *>(dev);

                    set_dev->set_values(string_values);

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

        if(dev != nullptr){
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

    SensorNetwork(MessageSystem &sys):
        system(sys),
        transmitting(5) {};

    int get_devices(std::string);
    int start_transmitting();
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

    std::vector<int> delays;

    std::cerr << "Have " << devices.size() << " devices\n";

    for (auto *dev : devices)
    {
        // Do stuff
        std::cout << "Starting transmission: " << dev->name << " with rate " << dev->rate << std::endl;
    }

    int clock = 0; // mby clock = 1

    while (true)
    {
        std::this_thread::sleep_for(1000ms);
        std::cerr << "Clk" << clock << "\n";

        for (auto *dev : devices)
        {
            if (clock % dev->rate == 0)
            {
                std::string msg = dev->generate_msg();
                system.send_message(dev->topic, msg.data(), msg.size());
                std::cerr << "Sent " << dev->topic << " - " << msg << "\n";
            }
        }

        clock++;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    // seeding rand
    srand (static_cast <unsigned> (time(0)));

    if(argc != 2){
        std::cerr << "Usage: ./sim URL\n";
        return 1;
    }

    std::string server_address = argv[1];

    MessageSystem sys("Tester", server_address);

    SensorNetwork network(sys);

    int ret = network.get_devices("test_config.cfg");
    if (ret)
    {
        return ret;
    }

    network.start_transmitting();

    return 0;
}