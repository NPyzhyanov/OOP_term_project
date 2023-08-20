#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "get_name.h"
#include "vehicle.h"
#include "land_vehicle.h"
#include "offroad_boots.h"

vehicle::Offroad_Boots::Offroad_Boots()
{
    id = vehicle::offroad_boots;
    vehicle_name = vehicle::get_name(id);
    speed = 6;
    performance_time = 60;
    rest_time[0] = 10;
    rest_time[1] = 5;
    rest_time[2] = 5;
}
