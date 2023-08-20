#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "vehicle.h"
#include "get_name.h"

std::string vehicle::get_name(vehicle::LandVehiclesList list_element)
{
    std::string name = "";
    
    switch(list_element)
    {
    case camel:
        name += "camel";
        break;
    case high_speed_camel:
        name += "high-speed camel";
        break;
    case centaur:
        name += "centaur";
        break;
    case offroad_boots:
        name += "offroad boots";
        break;
    case terminal_land_vehicle:
        name += vehicle::get_terminal_code_phrase();
        break;
    default:
        name += "unknown land vehicle";
        break;
    }
    
    return name;
}

std::string vehicle::get_name(vehicle::AirVehiclesList list_element)
{
    std::string name = "";
    
    switch(list_element)
    {
    case flying_carpet:
        name += "flying carpet";
        break;
    case eagle:
        name += "eagle";
        break;
    case broom:
        name += "broom";
        break;
    case terminal_air_vehicle:
        name += vehicle::get_terminal_code_phrase();
        break;
    default:
        name += "unknown air vehicle";
        break;
    }
    
    return name;
}
