#ifndef CHECKIN_H
#define CHECKIN_H

#if defined(CHECKIN_LIBRARY)
#define CHECKIN_API __declspec(dllexport)
#else
#define CHECKIN_API __declspec(dllimport)
#endif

namespace checkin
{
    enum RacingType
    {
        land,
        air,
        combined
    };
    
    enum VehicleStatus
    {
        available,
        registered
    };
    
    enum ReturnCode
    {
        ok,
        try_again,
        action_impossible
    };
    
    class Vehicle
    {
    public:
        Vehicle(std::string _name);
        ~Vehicle();
        
        std::string get_name();
        VehicleStatus get_status();
        void register_it();
        
    private:
        std::string name;
        VehicleStatus status;
    };
    
    checkin::Vehicle** browse_list(std::string* p_list, std::string terminal_codephrase, int* vehicles_amount);
    void copy_available_vehicles(checkin::Vehicle** destination_array, int dest_arr_size, checkin::Vehicle** &source_array_1, int src_arr_1_size, checkin::Vehicle** &source_array_2, int src_arr_2_size);

    class Checkin
    {
    public:
        Checkin(int _known_vcls_amount, checkin::Vehicle** _known_vehicles);
        Checkin(const Checkin&) = delete;
        Checkin& operator=(const Checkin&) = delete;
        ~Checkin();
        
        CHECKIN_API int get_available_vcls_amount();
        CHECKIN_API int get_registered_vcls_amount();
        CHECKIN_API std::string show_available_vehicles();
        CHECKIN_API std::string show_registered_vehicles();
        
        CHECKIN_API ReturnCode register_vehicle(int order_number);
        CHECKIN_API ReturnCode run_vehicles_preparation(garage::Garage* p_garage);
        
    private:
        int known_vcls_amount;
        int available_vcls_amount;
        int registered_vcls_amount;
        checkin::Vehicle** known_vehicles;
    };
    
    CHECKIN_API Checkin* start_checkin(RacingType racing_type);
}

#endif // CHECKIN_H
