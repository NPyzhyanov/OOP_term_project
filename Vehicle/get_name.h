#ifndef GET_NAME_H
#define GET_NAME_H

namespace vehicle
{
    std::string get_name(vehicle::LandVehiclesList list_element, std::string identifier);
    std::string get_name(vehicle::AirVehiclesList list_element, std::string identifier);
}

#endif // GET_NAME_H
