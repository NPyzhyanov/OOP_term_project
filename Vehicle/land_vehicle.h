#ifndef LAND_VEHICLE_H
#define LAND_VEHICLE_H

namespace vehicle
{
    class Land_Vehicle : public vehicle::Vehicle
    {
    public:
        Land_Vehicle();
        
        double ready_set_go(double distance) override;
        
    protected:
        double performance_time;
        double rest_time[3];
        
        LandVehiclesList id;
        
    };
}

#endif // LAND_VEHICLE_H
