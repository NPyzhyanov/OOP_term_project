#include <string>

#include "land_vehicles_list.h"
#include "vehicle.h"
#include "land_vehicle.h"

vehicle::Land_Vehicle::Land_Vehicle()
{
}

//vehicle::Land_Vehicle::~Land_Vehicle()
//{
//}

double vehicle::Land_Vehicle::ready_set_go(double distance)
{
    check_inputs(distance);
    
    if (distance == 0.0)
    {
        return 0.0;
    }
    
    double result_time = distance / speed;
    
    int stops_number = static_cast<int>(result_time / performance_time);
    if((result_time / performance_time - stops_number) == 0.0)
    {
        stops_number--;
    }
    
    for (int i = 0; i < stops_number; i++)
    {
        if (i > 1)
        {
            result_time += rest_time[2];
        }
        else
        {
            result_time += rest_time[i];
        }
    }
    
    return result_time;
}
