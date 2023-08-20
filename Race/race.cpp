#include <stdexcept>
#include <string>
#include <cmath>
#include <float.h>

#include "vehicle.h"
#include "race.h"

race::Race* race::create_race(double _distance)
{
    if (_distance < 0)
    {
        throw std::logic_error("race::create_race : (_distance < 0)");
    }
    
    race::Race* p_r1 = new race::Race(_distance);
    return p_r1;
}

race::Race::Race(double _distance)
{
    distance = _distance;
    participants_amount = 0;
    race_results = nullptr;
}

race::Race::~Race()
{
    delete[] race_results;
    race_results = nullptr;
}

void race::Race::start_race(int _participants_amount, vehicle::Vehicle** p_vehicles_array)
{
    if (_participants_amount < 2)
    {
        throw std::logic_error("race::Race::start_race : (_participants_amount < 2)");
    }
    if (p_vehicles_array == nullptr)
    {
        throw std::logic_error("race::Race::start_race : (p_vehicles_array == nullptr)");
    }
    
    participants_amount = _participants_amount;
    
    race_results = new race::Result[_participants_amount];
    
    for (int i = 0; i < _participants_amount; i++)
    {
        race_results[i].name = p_vehicles_array[i]->get_instance_name();
        race_results[i].time = p_vehicles_array[i]->ready_set_go(distance);
        race_results[i].rank = 0;
    }
}

void race::Race::sort_results()
{
    bool all_participants_ranked = false;
    int current_position = 0;
    while(!all_participants_ranked)
    {
        current_position++;
        all_participants_ranked = true;
        double the_lowest_time = DBL_MAX;
        int the_fastest_index = participants_amount;
        for (int i = 0; i < participants_amount; i++)
        {
            if (race_results[i].rank == 0)
            {
                all_participants_ranked = false;
                if (race_results[i].time < the_lowest_time)
                {
                    the_lowest_time = race_results[i].time;
                    the_fastest_index = i;
                }
            }
        }
        if (!all_participants_ranked)
        {
            if (the_fastest_index >= participants_amount)
            {
                throw std::logic_error("race::Race::sort_results : (the_fastest_index >= participants_amount)");
            }
            race_results[the_fastest_index].rank = current_position;
        }
    }
}

std::string race::round_and_convert(double number, int decimal_places)
{
    double prerounded_number = round(pow(10.0, 1.0 * decimal_places) * number) / pow(10.0, 1.0 * decimal_places);
    
    int integer_part = static_cast<int>(prerounded_number);
    std::string output_string = std::to_string(integer_part);
    
    if (decimal_places > 0)
    {
        output_string += ".";
        int fractional_part = static_cast<int>(prerounded_number * pow(10.0, 1.0 * decimal_places)) % static_cast<int>(pow(10.0, 1.0 * decimal_places));
        output_string += std::to_string(fractional_part);
    }
    
    return output_string;
}

std::string race::Race::show_results()
{
    if (race_results == nullptr)
    {
        throw std::logic_error("race::Race::show_results : (race_results == nullptr)");
    }
    
    race::Race::sort_results();
    
    std::string output_string = "Results:\n\trank\t|\ttime\t|\tname\n";
    
    for (int current_position = 1; current_position <= participants_amount; current_position++)
    {
        for (int i = 0; i < participants_amount; i++)
        {
            if (race_results[i].rank == current_position)
            {
                output_string += "\t";
                output_string += std::to_string(current_position);
                output_string += "\t|\t";
                output_string += race::round_and_convert(race_results[i].time, 2);
                output_string += "\t|\t";
                output_string += race_results[i].name;
                output_string += "\n";
                break;
            }
        }
    }
    return output_string;
}
