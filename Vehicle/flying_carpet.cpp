#include <string>

#include "land_vehicles_list.h"
#include "air_vehicles_list.h"
#include "get_name.h"
#include "vehicle.h"
#include "air_vehicle.h"
#include "flying_carpet.h"

vehicle::Flying_Carpet::Flying_Carpet()
{
    id = vehicle::flying_carpet;
    vehicle_name = vehicle::get_name(id, "air");
    speed = 10;
}

double vehicle::Flying_Carpet::decrease_distance(double distance)
{
    if (distance < 1000)
    {
        return distance;
    }
    else if (distance < 5000)
    {
        return 0.97 * distance;
    }
    else if (distance < 10000)
    {
        return 0.90 * distance;
    }
    else
    {
        return 0.95 * distance;
    }
}
