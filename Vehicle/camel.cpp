#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "vehicle.h"
#include "get_name.h"
#include "land_vehicle.h"
#include "camel.h"

vehicle::Camel::Camel()
{
    id = vehicle::camel;
    vehicle_name = vehicle::get_name(id, "land");
    speed = 10;
    performance_time = 30;
    rest_time[0] = 5;
    rest_time[1] = 8;
    rest_time[2] = 8;
}
