#ifndef FLYING_CARPET_H
#define FLYING_CARPET_H

//#if defined(VEHICLE_LIBRARY)
//#define VEHICLE_API __declspec(dllexport)
//#else
//#define VEHICLE_API __declspec(dllimport)
//#endif

namespace vehicle
{
    class Flying_Carpet : public vehicle::Air_Vehicle
    {
    public:
        Flying_Carpet();
        
    private:
        double decrease_distance(double distance) override;
    };
}

#endif // FLYING_CARPET_H
