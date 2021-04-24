#ifndef MQTT_SIM_DEV
#define MQTT_SIM_DEV

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

class sim_device
{
public:

    // vlastnosti vsech devices
    std::string name;
    std::string topic;
    int rate;

public:

    virtual std::string generate_msg() = 0;

    sim_device()
    {
        std::cout << "Constructing sim_device \n";
    }

    void set_name(std::string new_name){
        name = new_name;
    }

    void set_topic(std::string new_topic){
        topic = new_topic;
    }

    void set_rate(int new_rate){
        rate = new_rate;
    }

    virtual ~sim_device()
    { std::cout << "Destructing sim_device \n"; }  
};

class float_sim_device : public sim_device {

    float min_val;
    float max_val;
    float max_delta;

    float current_value;

public:
    float_sim_device()
    {
        std::cout << "Constructing float_sim_device \n";
    }

    virtual std::string generate_msg() override {
        std::cout << "float device " << name <<  " generating msg\n";
        return "float msg";
    }

    virtual ~float_sim_device()
    { std::cout << "Destructing float_sim_device \n"; }  
};

class value_set_device : public sim_device {

    std::vector<std::string> values;

public:
    value_set_device()
    {
        std::cout << "Constructing float_sim_device \n";
    }

    virtual std::string generate_msg() override {
        std::cout << "set device " << name <<  " generating msg\n";
        return "float msg";
    }

    virtual ~value_set_device()
    { std::cout << "Destructing float_sim_device \n"; }  
};

/*

// todo delete
    float current_value;

    bool has_range;
    bool has_set_of_values;

    std::vector<std::string> values;
    std::unordered_map<std::string, float> properties;

void finalize(){

        auto min_val = properties.find("min-val");
        auto max_val = properties.find("max-val");
        auto max_delta = properties.find("max-delta");
        auto change_chance = properties.find("change-chance");

        if(min_val != properties.end() && max_val != properties.end()){
            has_range = true;
            current_value = 1.0f;
        }

        if(change_chance != properties.end() && values.size() != 0){
            has_set_of_values = true;
        }
    }
*/

#endif