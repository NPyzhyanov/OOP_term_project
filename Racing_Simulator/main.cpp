#include <iostream>
#include <string>

#include "vehicle.h"

int main()
{
    const double DISTANCE = 8500;
    
    std::string code_phrase = vehicle::get_terminal_code_phrase();
    
    std::cout << "Land vehicles: " << std:: endl;
    
    bool list_got = false;
    int l_counter = 0;
    std::string* p_l_list = vehicle::get_land_vehicles_list();
    while (!list_got)
    {
        std::string current_word = p_l_list[l_counter];
        if (current_word == code_phrase || l_counter >= 100)
        {
            list_got = true;
        }
        else
        {
            std::cout << ++l_counter << ". " << current_word << std::endl;
        }
    }
    
    std::cout << "\nAir vehicles: " << std:: endl;
    
    list_got = false;
    int a_counter = 0;
    std::string* p_a_list = vehicle::get_air_vehicles_list();
    while (!list_got)
    {
        std::string current_word = p_a_list[a_counter];
        if (current_word == code_phrase || a_counter >= 100)
        {
            list_got = true;
        }
        else
        {
            std::cout << ++a_counter << ". " << current_word << std::endl;
        }
    }
    
    std::cout << std::endl;
    
    vehicle::Vehicle* p_land_vehicles_array[l_counter];
    for (int i = 0; i < l_counter; i++)
    {
        p_land_vehicles_array[i] = vehicle::create_vehicle(p_l_list[i]);
        std::cout << p_land_vehicles_array[i]->get_instance_name() << " created" << std::endl;
    }
    
    vehicle::Vehicle* p_air_vehicles_array[a_counter];
    for (int i = 0; i < a_counter; i++)
    {
        p_air_vehicles_array[i] = vehicle::create_vehicle(p_a_list[i]);
        std::cout << p_air_vehicles_array[i]->get_instance_name() << " created" << std::endl;
    }
    
    double land_vcls_results[l_counter];
    
    for (int i = 0; i < l_counter; i++)
    {
        land_vcls_results[i] = p_land_vehicles_array[i]->ready_set_go(DISTANCE);
    }
    
    double air_vcls_results[a_counter];
    
    for (int i = 0; i < a_counter; i++)
    {
        air_vcls_results[i] = p_air_vehicles_array[i]->ready_set_go(DISTANCE);
    }
    
    std::cout << "\nRESULTS\n\n";
    
    for (int i = 0; i < l_counter; i++)
    {
        std::cout << p_land_vehicles_array[i]->get_instance_name() << "\t\t" << land_vcls_results[i] << std::endl;
    }
    for (int i = 0; i < a_counter; i++)
    {
        std::cout << p_air_vehicles_array[i]->get_instance_name() << "\t\t" << air_vcls_results[i] << std::endl;
    }
    
    for (int i = 0; i < l_counter; i++)
    {
        vehicle::delete_vehicle(p_land_vehicles_array[i]);
    }
    for (int i = 0; i < a_counter; i++)
    {
        vehicle::delete_vehicle(p_air_vehicles_array[i]);
    }
    
    vehicle::delete_list(p_l_list);
    vehicle::delete_list(p_a_list);
    
    return 0;
}

