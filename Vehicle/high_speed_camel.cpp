#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "get_name.h"
#include "vehicle.h"
#include "land_vehicle.h"
#include "high_speed_camel.h"

vehicle::High_Speed_Camel::High_Speed_Camel()
{
    id = vehicle::high_speed_camel;
    vehicle_name = vehicle::get_name(id, "land");
    speed = 40;
    performance_time = 10;
    rest_time[0] = 5;
    rest_time[1] = 6.5;
    rest_time[2] = 8;
}
