#ifndef EAGLE_H
#define EAGLE_H

//#if defined(VEHICLE_LIBRARY)
//#define VEHICLE_API __declspec(dllexport)
//#else
//#define VEHICLE_API __declspec(dllimport)
//#endif

namespace vehicle
{
    class Eagle : public vehicle::Air_Vehicle
    {
    public:
        Eagle();
        
    private:
        double decrease_distance(double distance) override;
    };
}

#endif // EAGLE_H
