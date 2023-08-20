#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "get_name.h"
#include "vehicle.h"
#include "land_vehicle.h"
#include "centaur.h"

vehicle::Centaur::Centaur()
{
    id = vehicle::centaur;
    vehicle_name = vehicle::get_name(id);
    speed = 15;
    performance_time = 8;
    rest_time[0] = 2;
    rest_time[1] = 2;
    rest_time[2] = 2;
}
