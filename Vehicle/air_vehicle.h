#ifndef AIR_VEHICLE_H
#define AIR_VEHICLE_H

namespace vehicle
{
    class Air_Vehicle : public vehicle::Vehicle
    {
    public:
        Air_Vehicle();
        
        double ready_set_go(double distance) override;
        
    protected:
        virtual double decrease_distance(double distance);
        
        AirVehiclesList id;
        
    };
}

#endif // AIR_VEHICLE_H
