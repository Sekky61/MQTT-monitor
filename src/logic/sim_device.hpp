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

    void set_min_val(float new_min_val){
        min_val = new_min_val;
    }

    void set_max_val(float new_max_val){
        max_val = new_max_val;
    }

    void set_max_delta(float new_max_delta){
        max_delta = new_max_delta;
    }

    virtual std::string generate_msg() override {
        return "float msg";
    }

    virtual ~float_sim_device()
    { std::cout << "Destructing float_sim_device \n"; }  
};

class value_set_device : public sim_device {

    float change_chance;

    std::vector<std::string> values;

public:
    value_set_device()
    {
        std::cout << "Constructing value_set_device \n";
    }

    virtual std::string generate_msg() override {
        return "value set msg";
    }

    void set_values(std::vector<std::string> new_values){
        values = new_values;
    }

    void set_change_chance(float new_change_chance){
        change_chance = new_change_chance;
    }

    virtual ~value_set_device()
    { std::cout << "Destructing float_sim_device \n"; }  
};

#endif