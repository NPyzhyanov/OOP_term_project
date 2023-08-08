#ifndef VEHICLE_H
#define VEHICLE_H

#if defined(VEHICLE_LIBRARY)
#define VEHICLE_API __declspec(dllexport)
#else
#define VEHICLE_API __declspec(dllimport)
#endif

namespace vehicle
{
    VEHICLE_API std::string get_terminal_code_phrase();
    
    VEHICLE_API std::string* get_land_vehicles_list();
    VEHICLE_API std::string* get_air_vehicles_list();
    
    VEHICLE_API void delete_list(std::string* str_array);
    
    class Vehicle
    {
    public:
        Vehicle();
        
        Vehicle(const Vehicle&) = delete;
        Vehicle& operator=(const Vehicle&) = delete;
        
        virtual ~Vehicle();
    
        VEHICLE_API virtual double ready_set_go(double distance);
        
        VEHICLE_API std::string get_instance_name();
        
    protected:
        void check_inputs(double distance);
        
        double speed;
        std::string vehicle_name;
        
    };
    
    VEHICLE_API Vehicle* create_vehicle(std::string vehicle_name);
    
    VEHICLE_API void delete_vehicle(vehicle::Vehicle* &p_vehicle);
    
}

#endif // VEHICLE_H
