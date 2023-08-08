#include <string>

#include "air_vehicles_list.h"
#include "vehicle.h"
#include "air_vehicle.h"

vehicle::Air_Vehicle::Air_Vehicle()
{
}

double vehicle::Air_Vehicle::decrease_distance(double distance)
{
    return distance;
}

double vehicle::Air_Vehicle::ready_set_go(double distance)
{
    vehicle::Air_Vehicle::check_inputs(distance);
    
    double decreased_distance = decrease_distance(distance);
    
    return decreased_distance / speed;
}
