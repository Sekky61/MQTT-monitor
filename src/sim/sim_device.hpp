/*! \file sim_device.hpp
    \brief Zarizeni simulujici provoz MQTT
    
    Trida sim_device a jeji potomci, simulujici provoz
    v MQTT
*/

#ifndef MQTT_SIM_DEV
#define MQTT_SIM_DEV

#include <string>
#include <vector>
#include <iostream>

#include <fstream>
#include <iterator>
#include <algorithm>

#include <cstdlib>

/** \class sim_device
 *  \brief Abstraktni virtualni trida simulovaneho pristroje
 * 
 *  Trida slouzi jako rozhrani pro volani generate_msg, set_value, set_values
 *  ze smycky simulatoru.
 * 
 */
class sim_device
{
    /**
     * Nazev pristroje. Pouziva se pri vypisu aktivity
     */
    std::string name;

    /**
     * Topic, na kterem pristroj vysila a prijima data
     */
    std::string topic;

    /**
     * Perioda vyslani signalu (v sekundach)
     */
    int rate;

public:

    /**
     * Ciste virtualni metoda.
     * 
     * Generuje zpravu pro odeslani do site.
     */
    virtual std::string generate_msg() = 0;

    /**
     * Ciste virtualni metoda.
     * 
     * Nastavuje hodnotu (typicky z prichozi zpravy)
     * 
     * \param value nova hodnota
     */
    virtual void set_value(std::string value) = 0;

    /**
     * Ciste virtualni metoda.
     * 
     * Nastavuje mnozinu hodnot, ktere muze zarizeni vysilat (neni implementovano v kazdem typu zarizeni)
     */
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
     * 
     * \return \ref name
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
     * 
     * \return \ref topic
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
     * 
     * \return \ref rate
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

/**
 * Zarizeni hlasici ciselnou hodnotu
 */
class float_sim_device : public sim_device {

    /**
     * Minimalni hodnota hlasena zarizenim
     */
    float min_val;

    /**
     * Maximalni hodnota hlasena zarizenim
     */
    float max_val;

    /**
     * Minimalni zmena hodnoty za periodu
     */
    float max_delta;

    /**
     * Signalizuje, jestli byla vygenerovana vychozi hodnota \ref current_value
     */
    bool initialized;

    /**
     * Aktualni hodnota zarizeni
     */
    float current_value;

public:

    /**
     * Konstruktor s vychozimi hodnotami
     */
    float_sim_device():
        min_val(0),
        max_val(100),
        max_delta(0.5),
        initialized(false),
        current_value(0)
    {
        std::cout << "Constructing float_sim_device \n";
    }

    /**
     * Nastavi novou \ref min_val
     */
    void set_min_val(float new_min_val){
        min_val = new_min_val;
    }

    /**
     * Nastavi novou \ref max_val
     */
    void set_max_val(float new_max_val){
        max_val = new_max_val;
    }

    /**
     * Nastavi novou \ref max_delta
     */
    void set_max_delta(float new_max_delta){
        max_delta = new_max_delta;
    }

    /**
     * Generuje textovou zpravu k vyslani do site.
     * 
     * Prvni volani inicializuje hodnotu pristroje.
     * Nova hodnota je v rozmezi <current_value-max_delta;current_value+max_delta>
     * 
     * \return Hodnota ze zarizeni v textove podobe
     */
    virtual std::string generate_msg() override {
        
        if(!initialized){
            // source: https://stackoverflow.com/questions/686353/random-float-number-generation
            current_value = min_val + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max_val-min_val)));
            initialized = true;
        }

        // increment in range <-max_delta;max_delta>
        float increment = -max_delta + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2*max_delta)));

        current_value += increment;

        current_value = std::max(current_value, min_val);
        current_value = std::min(current_value, max_val);

        return std::to_string(current_value);
    }

    /**
     * Nastavi novou hodnotu zarizeni \ref current_value
     * 
     * Typicky prichozi data ze site.
     */
    virtual void set_value(std::string value) override {
        current_value = std::stof(value);
    }

    /**
     * Neni implementovano.
     * 
     * \throw std::exception
     */
    virtual void set_values(std::vector<std::string>) override {
        throw new std::exception;
    }

    /**
     * Destruktor
     */
    virtual ~float_sim_device()
    { std::cout << "Destructing float_sim_device \n"; }  
};

/**
 * Zarizeni hlasici jednu z mnoziny definovanych hodnot
 */
class value_set_device : public sim_device {

    /**
     * Pravdepodobnost, ze se po periode vygeneruje nova nahodna hodnota
     */
    float change_chance;

    /**
     * Signalizuje, jestli byla vygenerovana vychozi hodnota \ref current_value
     */
    bool initialized;

    /**
     * Aktualni hodnota zarizeni. Jedna z \ref values
     */
    std::string current_value;

    /**
     * Mnozina hodnot, kterych muze zarizeni nabyt
     */
    std::vector<std::string> values;

public:
    /**
     * Konstruktor
     */
    value_set_device() : 
        initialized(false)
    {
        std::cout << "Constructing value_set_device \n";
    }

    /**
     * Generuje zpravu
     * 
     * Prvni volani inicializuje \ref current_value
     * 
     * \return Zprava pripravena k vyslani po siti
     */
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

    /**
     * Nastavi novou hodnotu \ref current_value
     * 
     * \param value nova hodnota
     */
    virtual void set_value(std::string value) override {
        current_value = value;
    }

    /**
     * Vrati jednu z hodnot \ref values
     * 
     * \return Nahodna hodnota z \ref values
     */
    std::string pick_random_value(){
        int index = rand() % values.size();
        return values[index];
    }

    /**
     * Definuje novou mnozinu hodnot, ktere muze zarizeni vysilat
     * 
     * \param new_values nova hodnota \ref values
     */
    virtual void set_values(std::vector<std::string> new_values) override {
        values = new_values;
    }

    /**
     * Definuje pravdepodobnost, ze si po periode \ref rate vybere nova hodnota z \ref values
     * 
     * \param new_change_chance nova hodnota \ref change_chance
     */
    void set_change_chance(float new_change_chance){
        change_chance = new_change_chance;
    }

    /**
     * Destruktor
     */
    virtual ~value_set_device()
    { std::cout << "Destructing float_sim_device \n"; }  
};

/**
 * Zarizeni zasilajici obrazek (obecne soubor)
 * 
 * Misto obrazku jsou v konfiguracnim souboru uvedeny jejich cesty.
 * Ty se funkci \ref file_paths_to_pictures nactou
 */
class picture_device : public sim_device {

    /**
     * Signalizuje, jestli byly soubory nacteny do pameti
     */
    bool initialized;

    /**
     * Pri inicializaci obsahuje cesty k souborum.
     * Po zavolani \ref file_paths_to_pictures je nahrazen daty v souberech v techto cestach
     */
    std::vector<std::string> values;

public:

    /**
     * Konstruktor
     */
    picture_device() : sim_device(), initialized(false)
    {
        std::cout << "Constructing picture_device \n";
    }

    /**
     * Vraci zpravu k odeslani po siti
     * 
     * Prvni volani nacte soubory uvedene ve vektoru \ref values
     * 
     *  \return obsah nahodneho souboru
     */
    virtual std::string generate_msg() override {

        if(!initialized){
            file_paths_to_pictures();
            initialized = true;
        }

        return pick_random_value();
    }

    /**
     * Nahradi vektor \ref values s cestami souboru
     * vektorem s obsahy souboru
     */
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

    /**
     * \return Nahodny prvek z mnoziny values
     */
    std::string pick_random_value(){
        int index = rand() % values.size();
        return values[index];
    }

    /**
     * Setter \ref values
     * 
     * \param new_values nova mnozina hodnot
     */
    virtual void set_values(std::vector<std::string> new_values) override {
        values = new_values;
    }

    /**
     * Neimplementovano
     */
    virtual void set_value(std::string value) override {
        (void)value;
    }

    /**
     * Destruktor
     */
    virtual ~picture_device()
    { std::cout << "Destructing picture_device \n"; }  
};

#endif