#ifndef CAMEL_H
#define CAMEL_H

//#if defined(VEHICLE_LIBRARY)
//#define VEHICLE_API __declspec(dllexport)
//#else
//#define VEHICLE_API __declspec(dllimport)
//#endif

namespace vehicle
{
    class Camel : public Land_Vehicle
    {
    public:
        Camel();
        
    };
}

#endif // CAMEL_H
