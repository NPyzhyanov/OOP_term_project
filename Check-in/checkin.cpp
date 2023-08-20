#include <stdexcept>
#include <string>

#include "vehicle.h"
#include "race.h"
#include "garage.h"
#include "checkin.h"

checkin::Checkin* checkin::start_checkin(checkin::RacingType racing_type)
{
    std::string terminal_codephrase = vehicle::get_terminal_code_phrase();
    
    int land_vcls_amount = 0;
    int air_vcls_amount = 0;
    
    checkin::Vehicle** land_vcls_ptrs = nullptr;
    checkin::Vehicle** air_vcls_ptrs = nullptr;
    checkin::Vehicle** vcls_ptrs = nullptr;
    
    if (racing_type == checkin::RacingType::land || racing_type == checkin::RacingType::combined)
    {
        std::string* p_land_list = vehicle::get_land_vehicles_list();
        land_vcls_ptrs = checkin::browse_list(p_land_list, terminal_codephrase, &land_vcls_amount);
        vehicle::delete_list(p_land_list);
    }
    
    if (racing_type == checkin::RacingType::air || racing_type == checkin::RacingType::combined)
    {
        std::string* p_air_list = vehicle::get_air_vehicles_list();
        air_vcls_ptrs = checkin::browse_list(p_air_list, terminal_codephrase, &air_vcls_amount);
        vehicle::delete_list(p_air_list);
    }
    
    int vehicles_amount = land_vcls_amount + air_vcls_amount;
    
    vcls_ptrs = new checkin::Vehicle*[vehicles_amount];
    checkin::copy_available_vehicles(vcls_ptrs, vehicles_amount, land_vcls_ptrs, land_vcls_amount, air_vcls_ptrs, air_vcls_amount);
    
    checkin::Checkin* p_c1 = new checkin::Checkin(vehicles_amount, vcls_ptrs);
    return p_c1;
}

checkin::Vehicle** checkin::browse_list(std::string* p_list, std::string terminal_codephrase, int* vehicles_amount)
{
    const int ALLOWED_ITERATIONS = 100;
    
    bool list_got = false;
    int iterations_counter = 0;
    int vehicles_counter = 0;
    while (!list_got)
    {
        iterations_counter++;
        if (iterations_counter >= ALLOWED_ITERATIONS)
        {
            throw std::runtime_error("checkin::browse_list : (iterations_counter >= ALLOWED_ITERATIONS)");
            break;
        }
        
        std::string current_word = p_list[vehicles_counter];
        
        if (current_word == terminal_codephrase)
        {
            list_got = true;
        }
        else
        {
            vehicles_counter++;
        }
    }
    
    const int local_vehicles_amount = vehicles_counter;
    *vehicles_amount = local_vehicles_amount;
    
    checkin::Vehicle** vehicles_ptrs_array = new checkin::Vehicle*[local_vehicles_amount];
    
    for (int i = 0; i < local_vehicles_amount; i++)
    {
        vehicles_ptrs_array[i] = new checkin::Vehicle(p_list[i]);
    }
    
    return vehicles_ptrs_array;
}

void checkin::copy_available_vehicles(checkin::Vehicle** destination_array, int dest_arr_size, checkin::Vehicle** &source_array_1, int src_arr_1_size, checkin::Vehicle** &source_array_2, int src_arr_2_size)
{
    if (dest_arr_size < 0 || src_arr_1_size < 0 || src_arr_2_size < 0)
    {
        throw std::logic_error("checkin::copy_available_vehicles : (dest_arr_size < 0 || src_arr_1_size < 0 || src_arr_2_size < 0)");
    }
    if (dest_arr_size != src_arr_1_size + src_arr_2_size)
    {
        throw std::logic_error("checkin::copy_available_vehicles : (dest_arr_size != src_arr_1_size + src_arr_2_size)");
    }
    
    for (int i = 0; i < src_arr_1_size; i++)
    {
        destination_array[i] = source_array_1[i];
        source_array_1[i] = nullptr;
    }
    for (int j = 0; j < src_arr_2_size; j++)
    {
        int i = src_arr_1_size + j;
        destination_array[i] = source_array_2[j];
        source_array_2[j] = nullptr;
    }
    
    delete[] source_array_1;
    source_array_1 = nullptr;
    delete[] source_array_2;
    source_array_2 = nullptr;
}

checkin::Checkin::Checkin(int _known_vcls_amount, checkin::Vehicle** _known_vehicles)
{
    if (_known_vcls_amount < 0)
    {
        throw std::logic_error("checkin::Checkin::Checkin : (_known_vcls_amount < 0)");
    }
    
    known_vcls_amount = _known_vcls_amount;
    available_vcls_amount = _known_vcls_amount;
    registered_vcls_amount = 0;
    known_vehicles = _known_vehicles;
}

checkin::Checkin::~Checkin()
{
    for (int i = 0; i < known_vcls_amount; i ++)
    {
        delete known_vehicles[i];
        known_vehicles[i] = nullptr;
    }
    delete[] known_vehicles;
    known_vehicles = nullptr;
}

int checkin::Checkin::get_available_vcls_amount()
{
    return available_vcls_amount;
}

int checkin::Checkin::get_registered_vcls_amount()
{
    return registered_vcls_amount;
}

std::string checkin::Checkin::show_available_vehicles()
{
    if (available_vcls_amount <= 0)
    {
        return "No more available vehicles\n";
    }
    
    int available_vcls_counter = 0;
    std::string output_string = "Available vehicles:\n";
    
    for (int i = 0; i < known_vcls_amount; i++)
    {
        if (known_vehicles[i]->get_status() == checkin::VehicleStatus::available)
        {
            available_vcls_counter++;
            output_string += "\t";
            output_string += std::to_string(available_vcls_counter);
            output_string += ". ";
            output_string += known_vehicles[i]->get_name();
            output_string += "\n";
        }
    }
    
    if (available_vcls_counter != available_vcls_amount)
    {
        throw std::logic_error("checkin::Checkin::show_available_vehicles : (available_vcls_counter != available_vcls_amount)");
    }
    
    return output_string;
}

std::string checkin::Checkin::show_registered_vehicles()
{
    if (registered_vcls_amount <= 0)
    {
        return "\nNo vehicle has been registered yet.";
    }
    
    int registered_vcls_counter = 0;
    std::string output_string = "\nRegistered vehicles:";
    
    for (int i = 0; i < known_vcls_amount; i++)
    {
        if (known_vehicles[i]->get_status() == checkin::VehicleStatus::registered)
        {
            output_string += registered_vcls_counter ? ", " : " ";
            registered_vcls_counter++;
            output_string += std::to_string(registered_vcls_counter);
            output_string += ". ";
            output_string += known_vehicles[i]->get_name(); 
        }
    }
    
    if (registered_vcls_counter != registered_vcls_amount)
    {
        throw std::logic_error("checkin::Checkin::show_registered_vehicles : (registered_vcls_counter != registered_vcls_amount)");
    }
    
    return output_string;
}

checkin::ReturnCode checkin::Checkin::register_vehicle(int order_number)
{
    if (available_vcls_amount <= 0)
    {
        return checkin::ReturnCode::action_impossible;
    }
    
    if(order_number <= 0 || order_number > available_vcls_amount)
    {
        return checkin::ReturnCode::try_again;
    }
    
    bool registered = false;
    int available_vcls_counter = 0;
    
    for (int i = 0; i < known_vcls_amount; i++)
    {
        if (known_vehicles[i]->get_status() == checkin::VehicleStatus::available)
        {
            available_vcls_counter++;
            if (available_vcls_counter == order_number)
            {
                known_vehicles[i]->register_it();
                available_vcls_amount--;
                registered_vcls_amount++;
                registered = true;
                break;
            }
        }
    }
    
    if (!registered)
    {
        throw std::logic_error("checkin::Checkin::register_vehicle : (!registered)");
    }
    
    return checkin::ReturnCode::ok;
}

checkin::ReturnCode checkin::Checkin::run_vehicles_preparation(garage::Garage* p_garage)
{
    if (registered_vcls_amount < 2)
    {
        return checkin::ReturnCode::try_again;
    }
    
    std::string* registered_vcls_names = new std::string[registered_vcls_amount];
    
    int registered_vcls_counter = 0;
    for (int i = 0; i < known_vcls_amount; i++)
    {
        if (known_vehicles[i]->get_status() == checkin::VehicleStatus::registered)
        {
            registered_vcls_names[registered_vcls_counter] = known_vehicles[i]->get_name();
            registered_vcls_counter++;
        }
    }
    
    if (registered_vcls_counter != registered_vcls_amount)
    {
        throw std::logic_error("checkin::Checkin::run_vehicles_preparation : (registered_vcls_counter != registered_vcls_amount)");
    }
    
    p_garage->create_new_vehicles(registered_vcls_amount, registered_vcls_names);
    
    delete[] registered_vcls_names;
    registered_vcls_names = nullptr;
    
    return checkin::ReturnCode::ok;
}

checkin::Vehicle::Vehicle(std::string _name)
{
    name = _name;
    status = checkin::VehicleStatus::available;
}

checkin::Vehicle::~Vehicle()
{
}

std::string checkin::Vehicle::get_name()
{
    return name;
}

checkin::VehicleStatus checkin::Vehicle::get_status()
{
    return status;
}

void checkin::Vehicle::register_it()
{
    if (status == checkin::VehicleStatus::registered)
    {
        throw std::logic_error("checkin::Vehicle::register_it : (status == checkin::VehicleStatus::registered)");
    }
    
    status = checkin::VehicleStatus::registered;
}
