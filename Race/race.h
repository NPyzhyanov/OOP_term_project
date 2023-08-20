#ifndef RACE_H
#define RACE_H

#if defined(RACE_LIBRARY)
#define RACE_API __declspec(dllexport)
#else
#define RACE_API __declspec(dllimport)
#endif

namespace race
{
    struct Result
    {
        std::string name;
        double time;
        int rank;
    };
    
    class Race
    {    
    public:
        Race(double _distance);
        
        Race(const Race&) = delete;
        Race& operator=(const Race&) = delete;
        
        ~Race();
        
        RACE_API void start_race(int _participants_amount, vehicle::Vehicle** p_vehicles_array);
        
        void sort_results();
        //void round_results(double decimal_places);
        
        RACE_API std::string show_results();
        
    private:
        double distance;
        
        int participants_amount;
        race::Result* race_results;
    };
    
    RACE_API Race* create_race(double _distance);
    std::string round_and_convert(double number, int decimal_places);
}

#endif // RACE_H
