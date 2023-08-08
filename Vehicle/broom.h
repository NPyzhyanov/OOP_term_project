#ifndef BROOM_H
#define BROOM_H

//#if defined(VEHICLE_LIBRARY)
//#define VEHICLE_API __declspec(dllexport)
//#else
//#define VEHICLE_API __declspec(dllimport)
//#endif

namespace vehicle
{
    class Broom : public vehicle::Air_Vehicle
    {
    public:
        Broom();
        
    private:
        double decrease_distance(double distance) override;
    };
}

#endif // BROOM_H
