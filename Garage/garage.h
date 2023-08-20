#ifndef GARAGE_H
#define GARAGE_H

#if defined(GARAGE_LIBRARY)
#define GARAGE_API __declspec(dllexport)
#else
#define GARAGE_API __declspec(dllimport)
#endif

namespace garage
{
    class Garage
    {
    public:
        Garage();
        Garage(const Garage&) = delete;
        Garage& operator=(const Garage&) = delete;
        ~Garage();
        
        GARAGE_API void create_new_vehicles(int updated_vehicles_amount, std::string* vehicles_names);
        GARAGE_API void prepare_participants(race::Race* p_race);
        
    private:
        vehicle::Vehicle*** vehicles_addresses_array_ptr;
        int vehicles_amount;
    };
    
    GARAGE_API garage::Garage* create_garage();
}

#endif // GARAGE_H
