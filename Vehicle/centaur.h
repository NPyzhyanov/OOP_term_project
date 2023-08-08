#ifndef CENTAUR_H
#define CENTAUR_H

//#if defined(VEHICLE_LIBRARY)
//#define VEHICLE_API __declspec(dllexport)
//#else
//#define VEHICLE_API __declspec(dllimport)
//#endif

namespace vehicle
{
    class Centaur : public Land_Vehicle
    {
    public:
        Centaur();
        
    };
}

#endif // CENTAUR_H
