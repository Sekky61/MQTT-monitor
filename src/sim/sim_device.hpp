#ifndef MQTT_SIM_DEV
#define MQTT_SIM_DEV

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

#include <fstream>
#include <iterator>
#include <algorithm>

#include <cstdlib>

/** \class sim_device
 *  \brief Abstraktni trida simulovaneho pristroje
 * 
 *  Trida slouzi jako rozhrani pro volani generate_msg()
 *  ze smycky simulatoru.
 * 
 */
class sim_device
{
    std::string name;
    std::string topic;
    int rate;

public:

    /**
     * Ciste virtualni metoda.
     * 
     * Generuje zpravu pro odeslani do site.
     */
    virtual std::string generate_msg() = 0;

    virtual void set_value(std::string) = 0;

    virtual void set_values(std::vector<std::string> new_values) = 0;

    /**
     * Konstruktor
     */
    sim_device()
    {
        std::cout << "Constructing sim_device \n";
    }

    /**
     * Setter pro atribut name
     * 
     * \param new_name nove jmeno pristroje
     */
    void set_name(std::string new_name){
        name = new_name;
    }

    /**
     * Getter pro atribut name
     */
    std::string get_name(){
        return name;
    }

    /**
     * Setter pro atribut topic
     * 
     * \param new_topic novy topic pod kterym bude pristroj publikovat
     */
    void set_topic(std::string new_topic){
        topic = new_topic;
    }

    /**
     * Getter pro atribut topic
     */
    std::string get_topic(){
        return topic;
    }

    /**
     * Setter pro atribut rate
     * 
     * \param new_rate nova perioda odesilani zpravy
     */
    void set_rate(int new_rate){
        rate = new_rate;
    }

    /**
     * Getter pro atribut rate
     */
    int get_rate(){
        return rate;
    }

    /**
     * Destruktor
     */
    virtual ~sim_device()
    { std::cout << "Destructing sim_device \n"; }  
};

class float_sim_device : public sim_device {

    float min_val;
    float max_val;
    float max_delta;

    bool seeded;
    float current_value;

public:
    float_sim_device():
        min_val(0),
        max_val(100),
        max_delta(0.5),
        seeded(false),
        current_value(0)
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
        
        if(!seeded){
            // source: https://stackoverflow.com/questions/686353/random-float-number-generation
            current_value = min_val + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max_val-min_val)));
            seeded = true;
        }

        // increment in range <-max_delta;max_delta>
        float increment = -max_delta + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2*max_delta)));

        current_value += increment;

        current_value = std::max(current_value, min_val);
        current_value = std::min(current_value, max_val);

        return std::to_string(current_value);
    }

    virtual void set_value(std::string msg) override {
        current_value = std::stof(msg);
    }

    virtual void set_values(std::vector<std::string>) override {
        throw new std::exception;
    }

    virtual ~float_sim_device()
    { std::cout << "Destructing float_sim_device \n"; }  
};

class value_set_device : public sim_device {

    float change_chance;

    bool initialized;
    std::string current_value;

    std::vector<std::string> values;

public:
    value_set_device() : 
        initialized(false)
    {
        std::cout << "Constructing value_set_device \n";
    }

    virtual std::string generate_msg() override {

        if(!initialized){
            current_value = pick_random_value();
            initialized = true;
        }

        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if(r<change_chance){
            // change current value
            current_value = pick_random_value();
        }

        return current_value;
    }

    virtual void set_value(std::string msg) override {
        current_value = msg;
    }

    std::string pick_random_value(){
        int index = rand() % values.size();
        return values[index];
    }

    virtual void set_values(std::vector<std::string> new_values) override {
        values = new_values;
    }

    void set_change_chance(float new_change_chance){
        change_chance = new_change_chance;
    }

    virtual ~value_set_device()
    { std::cout << "Destructing float_sim_device \n"; }  
};

class picture_device : public sim_device {

    bool initialized;

    std::vector<std::string> values;

public:
    picture_device() : sim_device(), initialized(false)
    {
        std::cout << "Constructing picture_device \n";
    }

    virtual std::string generate_msg() override {

        if(!initialized){
            file_paths_to_pictures();
            initialized = true;
        }

        return pick_random_value();
    }

    void file_paths_to_pictures(){
        std::vector<std::string> new_vals;
        for(auto path : values){
            std::ifstream input( path, std::ios::binary );

            std::string str((std::istreambuf_iterator<char>(input)),
                 std::istreambuf_iterator<char>());

            new_vals.push_back(str);
        }
        values = new_vals;
    }

    std::string pick_random_value(){
        int index = rand() % values.size();
        return values[index];
    }

    virtual void set_values(std::vector<std::string> new_values) override {
        values = new_values;
    }

    virtual void set_value(std::string msg) override {
        (void)msg;
    }

    virtual ~picture_device()
    { std::cout << "Destructing picture_device \n"; }  
};

#endif