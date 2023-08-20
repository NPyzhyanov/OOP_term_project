#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "get_name.h"
#include "vehicle.h"
#include "air_vehicle.h"
#include "broom.h"

vehicle::Broom::Broom()
{
    id = vehicle::broom;
    vehicle_name = vehicle::get_name(id);
    speed = 20;
}

double vehicle::Broom::decrease_distance(double distance)
{
    if (distance > 99000)
    {
        return 0.01 * distance;
    }
    else
    {
        int decrease_percentage = static_cast<int>(distance) / 1000;
        return static_cast<double>(100 - decrease_percentage) / 100.0 * distance;
    }
}
