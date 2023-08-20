#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "get_name.h"
#include "vehicle.h"
#include "air_vehicle.h"
#include "eagle.h"

vehicle::Eagle::Eagle()
{
    id = vehicle::eagle;
    vehicle_name = vehicle::get_name(id);
    speed = 8;
}

double vehicle::Eagle::decrease_distance(double distance)
{
    return 0.94 * distance;
}
