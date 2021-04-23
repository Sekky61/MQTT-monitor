#include "message_system.hpp"

#include <iostream>

#include <string>
#include <unordered_map>

#include <fstream>
#include <streambuf>

class Device
{
public:
    std::string name;

    std::unordered_map<std::string, std::string> properties;

public:
    Device(std::string name) : name(name){};
};

class ConfigReader
{

    std::string config_content;
    std::stringstream buffer;

    std::vector<Device> devices;

    enum Parser
    {
        Header,
        Empty,
        DeviceName,
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

    int parse_file()
    {
        std::string line;

        Parser state = Parser::Header;

        Device dev("");

        while (std::getline(buffer, line))
        {
            switch (state)
            {
            case Parser::Header:
                if (line != "mqtt-sim-config")
                {
                    std::cerr << "Parse error: header: " << line << std::endl;
                    return 1;
                }
                state = Parser::Empty;
                break;

            case Parser::Empty:
                if (line != "")
                {
                    std::cerr << "Parse error: empty: " << line << std::endl;
                    return 1;
                }
                state = Parser::DeviceName;
                break;

            case Parser::DeviceName:
                dev = Device(line);
                devices.push_back(dev);
                state = Parser::Param;
                break;

            case Parser::Param:
                if (line == "")
                {
                    state = Parser::Empty;
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
                    if(tokens.size() != 2){
                        std::cerr << "Parse error: neocekavana mezera. radek: " << line << std::endl;
                        return 1;
                    }
                    devices.back().properties[tokens[0]] = tokens[1];
                    state = Parser::Param;
                }
                break;
            }
        }

        return 0;
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

    SensorNetwork(MessageSystem &sys);
};

SensorNetwork::SensorNetwork(MessageSystem &sys) : system(sys)
{
    transmitting = 5;
}

int main(int argc, char *argv[])
{
    MessageSystem sys("Tester", "tcp://localhost:1888");

    //SensorNetwork home(sys);

    ConfigReader cfg("test_config.cfg");

    std::cerr << cfg.get_buffer().str() << std::endl;

    cfg.parse_file();

    return 0;
}