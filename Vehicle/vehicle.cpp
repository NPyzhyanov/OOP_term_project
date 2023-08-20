#include <stdexcept>
#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "vehicle.h"
#include "get_name.h"

#include "land_vehicle.h"
#include "air_vehicle.h"
#include "camel.h"
#include "high_speed_camel.h"
#include "centaur.h"
#include "offroad_boots.h"
#include "flying_carpet.h"
#include "eagle.h"
#include "broom.h"

std::string vehicle::get_terminal_code_phrase()
{
    return "end of vehicles' list";
}

std::string* vehicle::get_land_vehicles_list()
{
    std::string* names_array = new std::string[static_cast<int>(vehicle::terminal_land_vehicle)];
    
    for (int i = static_cast<int>(vehicle::null_land_vehicle); i < static_cast<int>(vehicle::terminal_land_vehicle) - 1; i++)
    {
        names_array[i] = vehicle::get_name(static_cast<vehicle::LandVehiclesList>(i+1));
    }
    
    names_array[vehicle::terminal_land_vehicle - 1] = vehicle::get_terminal_code_phrase();
    
    return names_array;
}

std::string* vehicle::get_air_vehicles_list()
{
    std::string* names_array = new std::string[static_cast<int>(vehicle::terminal_air_vehicle)];
    
    for (int i = static_cast<int>(vehicle::null_air_vehicle); i < static_cast<int>(vehicle::terminal_air_vehicle) - 1; i++)
    {
        names_array[i] = vehicle::get_name(static_cast<vehicle::AirVehiclesList>(i+1));
    }
    
    names_array[vehicle::terminal_air_vehicle - 1] = vehicle::get_terminal_code_phrase();
    
    return names_array;
}

void vehicle::delete_list(std::string* str_array)
{
    delete[] str_array;
    str_array = nullptr;
}

vehicle::Vehicle::Vehicle()
{
    speed = 0.0;
    vehicle_name = "unnamed_vehicle";
}

vehicle::Vehicle::~Vehicle()
{
}

double vehicle::Vehicle::ready_set_go(double distance)
{
    return 0.0 * distance;
}

std::string vehicle::Vehicle::get_instance_name()
{
    return vehicle_name;
}

void vehicle::Vehicle::check_inputs(double distance)
{
    if (distance < 0)
    {
        throw std::logic_error("vehicle::Vehicle::check_inputs : (distance < 0)");
    }
    
    if (speed <= 0)
    {
        throw std::logic_error("vehicle::Vehicle::check_inputs : (speed <= 0)");
    }
}

vehicle::Vehicle* vehicle::create_vehicle(std::string vehicle_name)
{
    vehicle::Vehicle* p_vehicle;
    
    if (vehicle_name == get_name(vehicle::camel))
    {
        p_vehicle = new vehicle::Camel();
    }
    else if (vehicle_name == get_name(vehicle::high_speed_camel))
    {
         p_vehicle = new vehicle::High_Speed_Camel();
    }
    else if (vehicle_name == get_name(vehicle::centaur))
    {
         p_vehicle = new vehicle::Centaur();
    }
    else if (vehicle_name == get_name(vehicle::offroad_boots))
    {
         p_vehicle = new vehicle::Offroad_Boots();
    }
    else if (vehicle_name == get_name(vehicle::flying_carpet))
    {
         p_vehicle = new vehicle::Flying_Carpet();
    }
    else if (vehicle_name == get_name(vehicle::eagle))
    {
         p_vehicle = new vehicle::Eagle();
    }
    else if (vehicle_name == get_name(vehicle::broom))
    {
         p_vehicle = new vehicle::Broom();
    }
    else
    {
        p_vehicle = nullptr;
    }
    
    return p_vehicle;
}

void vehicle::delete_vehicle(vehicle::Vehicle* p_vehicle)
{
    delete p_vehicle;
}
