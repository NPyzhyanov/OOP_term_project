#include <stdexcept>
#include <string>

#include "vehicle.h"
#include "race.h"
#include "garage.h"

garage::Garage* garage::create_garage()
{
    garage::Garage* p_g1 = new garage::Garage();
    return p_g1;
}

garage::Garage::Garage()
{
    vehicles_addresses_array_ptr = nullptr;
    vehicles_amount = 0;
}

garage::Garage::~Garage()
{
    for(int i = 0; i < vehicles_amount; i++)
    {
        vehicle::delete_vehicle((*vehicles_addresses_array_ptr)[i]);
        (*vehicles_addresses_array_ptr)[i] = nullptr;
    }
    delete[] (*vehicles_addresses_array_ptr);
    (*vehicles_addresses_array_ptr) = nullptr;
    delete vehicles_addresses_array_ptr;
    vehicles_addresses_array_ptr = nullptr;
}

void garage::Garage::create_new_vehicles(int updated_vehicles_amount, std::string* vehicles_names)
{
    if (updated_vehicles_amount < vehicles_amount || updated_vehicles_amount <= 1)
    {
        throw std::logic_error("garage::Garage::create_new_vehicles : (updated_vehicles_amount < vehicles_amount || updated_vehicles_amount <= 1)");
    }
    
    vehicle::Vehicle*** new_vehicles_addresses_array_ptr = new vehicle::Vehicle**;          // Создаём указатель типа vehicle::Vehicle**
    (*new_vehicles_addresses_array_ptr) = new vehicle::Vehicle*[updated_vehicles_amount];   // Создаём массив указателей типа vehicle::Vehicle*
    
    //int start_index = 0;
    int extra_vehicles_amount = updated_vehicles_amount - vehicles_amount;
    std::string* extra_vehicles_names = nullptr;
    std::string* prepared_vehicles_names = nullptr;
    
    if (vehicles_amount == 0)
    {
        if (vehicles_addresses_array_ptr != nullptr)
        {
            throw std::logic_error("garage::Garage::create_new_vehicles : (vehicles_amount == 0) && (vehicles_addresses_array_ptr != nullptr)");
        }
        prepared_vehicles_names = vehicles_names;
    }
    else
    {
        if (vehicles_addresses_array_ptr == nullptr)
        {
            throw std::logic_error("garage::Garage::create_new_vehicles : (vehicles_amount != 0) && (vehicles_addresses_array_ptr == nullptr)");
        }
        
        extra_vehicles_names = new std::string[extra_vehicles_amount];
        int extra_vehicles_counter = 0;
        
        for (int j = 0; j < updated_vehicles_amount; j++)
        {
            bool vehicle_j_found = false;
            for (int i = 0; i < vehicles_amount; i++)
            {
                if (vehicles_names[j] == (*vehicles_addresses_array_ptr)[i]->get_instance_name())
                {
                    vehicle_j_found = true;
                    break;
                }
            }
            if (!vehicle_j_found)
            {
                extra_vehicles_names[extra_vehicles_counter] = vehicles_names[j];
                extra_vehicles_counter++;
            }
        }
        
        if (extra_vehicles_counter != extra_vehicles_amount)
        {
            throw std::logic_error("garage::Garage::create_new_vehicles : (extra_vehicles_counter != extra_vehicles_amount)");
        }
        
        prepared_vehicles_names = extra_vehicles_names;
        
        for (int i = 0; i < vehicles_amount; i++)
        {
            (*new_vehicles_addresses_array_ptr)[i] = (*vehicles_addresses_array_ptr)[i];    // Инициализируем первые (vehicles_amount) элементов массива указателей типа vehicle::Vehicle* адресами ранее созданных объектов типа vehicle::Vehicle
            (*vehicles_addresses_array_ptr)[i] = nullptr;
        }
        
        delete[] (*vehicles_addresses_array_ptr);   // Удаляем старый массив указателей типа vehicle::Vehicle*
        (*vehicles_addresses_array_ptr) = nullptr;
        delete vehicles_addresses_array_ptr;        // Удаляем старый указатель типа vehicle::Vehicle**
        vehicles_addresses_array_ptr = nullptr;
    }
    
    for (int i = 0; i < extra_vehicles_amount; i++)
    {
        (*new_vehicles_addresses_array_ptr)[vehicles_amount + i] = vehicle::create_vehicle(prepared_vehicles_names[i]); // Инициализируем остальные элементы массива указателей типа vehicle::Vehicle* адресами вновь созданных объектов типа vehicle::Vehicle
    }
    
    delete[] extra_vehicles_names;
    extra_vehicles_names = nullptr;
    
    vehicles_amount = updated_vehicles_amount;
    vehicles_addresses_array_ptr = new_vehicles_addresses_array_ptr;
    new_vehicles_addresses_array_ptr = nullptr;
}

void garage::Garage::prepare_participants(race::Race* p_race)
{
    if (vehicles_amount < 2)
    {
        throw std::logic_error("garage::Garage::prepare_participants : (vehicles_amount < 2)");
    }
    if (vehicles_addresses_array_ptr == nullptr || (*vehicles_addresses_array_ptr) == nullptr)
    {
        throw std::logic_error("garage::Garage::prepare_participants : (vehicles_addresses_array_ptr == nullptr || (*vehicles_addresses_array_ptr) == nullptr)");
    }
    
    p_race->start_race(vehicles_amount, (*vehicles_addresses_array_ptr));
}
