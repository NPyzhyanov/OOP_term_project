#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>

#include "vehicle.h"
#include "race.h"
#include "garage.h"
#include "checkin.h"

int main()
{
    bool repeat_race = true;
    
    try
    {
        while (repeat_race)
        {
            checkin::Checkin* p_checkin = nullptr;
            garage::Garage* p_garage = nullptr;
            race::Race* p_race = nullptr;
            
            std::string saved_information = "";
            const std::string wrong_input_message = "Wrong input! Please try again.\n";
            
            checkin::RacingType racing_type;
            bool racing_type_choosing_finished = true;
            do
            {
                std::cout << (racing_type_choosing_finished ? "Welcome to the racing simulator!\n" : wrong_input_message);
                std::cout << "Enter the type of racing (1-3):\n";
                std::cout << "\t1. Racing for land vehicles\n";
                std::cout << "\t2. Racing for air vehicles\n";
                std::cout << "\t3. Racing for both land and air vehicles\n";
                
                std::string user_racing_type;
                std::cin >> user_racing_type;
                
                if (user_racing_type == "1")
                {
                    racing_type = checkin::RacingType::land;
                    saved_information += "Racing for land vehicles.";
                    racing_type_choosing_finished = true;
                }
                else if (user_racing_type == "2")
                {
                    racing_type = checkin::RacingType::air;
                    saved_information += "Racing for air vehicles.";
                    racing_type_choosing_finished = true;
                }
                else if (user_racing_type == "3")
                {
                    racing_type = checkin::RacingType::combined;
                    saved_information += "Racing for land and air vehicles.";
                    racing_type_choosing_finished = true;
                }
                else
                {
                    racing_type_choosing_finished = false;
                }
                std::system("cls");
            }
            while(!racing_type_choosing_finished);
            
            p_checkin = checkin::start_checkin(racing_type);
            
            double distance = 0.0;
            bool distance_entered = true;
            do
            {
                std::cout << (distance_entered ? (saved_information + "\n") : wrong_input_message);
                std::cout << "Enter distance (must be positive): ";
                std::string user_distance;
                std::cin >> user_distance;
                distance = stod(user_distance);
                if (distance <= 0.0)
                {
                    distance_entered = false;
                }
                else
                {
                    saved_information += " Distance: ";
                    saved_information += std::to_string(static_cast<int>(distance));
                    saved_information += "\n";
                    distance_entered = true;
                }
                std::system("cls");
            }
            while(!distance_entered);
            
            p_race = race::create_race(distance);
            p_garage = garage::create_garage();
            
            bool registration_completely_finished = false;
            std::string outer_try_again_message = "";
            while (!registration_completely_finished)
            {
                int registered_vcls_amount = p_checkin->get_registered_vcls_amount();
                bool starting_allowed = (registered_vcls_amount >= 2);
                std::string registration_information = (registered_vcls_amount ? p_checkin->show_registered_vehicles() : "");
                
                std::cout << outer_try_again_message << saved_information << registration_information << std::endl;
                outer_try_again_message = "";
                if (!starting_allowed)
                {
                    std::cout << "Please, register at least two vehicles.\n";
                }
                std::cout << "Choose action:\n";
                
                int action_number = 0;
                int registration_action_number = 0;
                int starting_action_number = 0;
                if (p_checkin->get_available_vcls_amount() > 0)
                {
                    action_number++;
                    registration_action_number = action_number;
                    std::cout << "\t" << std::to_string(registration_action_number) << ". Register vehicles\n";
                }
                if (starting_allowed)
                {
                    action_number++;
                    starting_action_number = action_number;
                    std::cout << "\t" << std::to_string(starting_action_number) << ". Start race\n";
                }
                
                std::string user_action;
                std::cin >> user_action;
                int action = std::stoi(user_action);
                
                if (registration_action_number && action == registration_action_number)
                {
                    std::string try_again_message = "";
                    bool current_registration_session_finished = false;
                    while (!current_registration_session_finished)
                    {
                        std::system("cls");
                        std::cout << try_again_message << saved_information << registration_information << std::endl;
                        try_again_message = "";
                        std::string available_vehicles_message = p_checkin->show_available_vehicles();
                        std::cout << available_vehicles_message;
                        std::cout << "\t0. Save choice and finish registration\n";
                        
                        std::string user_vehicle_choice;
                        std::cin >> user_vehicle_choice;
                        int vehicle_choice = stoi(user_vehicle_choice);
                        
                        if (vehicle_choice == 0)
                        {
                            checkin::ReturnCode vehicles_preparation_result = p_checkin->run_vehicles_preparation(p_garage);
                            if (vehicles_preparation_result == checkin::ReturnCode::try_again)
                            {
                                try_again_message = "Cannot finish registration. Not enough vehicles registered.\n";
                            }
                            else
                            {
                                current_registration_session_finished = true;
                            }
                        }
                        else if (vehicle_choice > p_checkin->get_available_vcls_amount())
                        {
                            try_again_message = wrong_input_message;
                        }
                        else
                        {
                            checkin::ReturnCode registration_result = p_checkin->register_vehicle(vehicle_choice);
                            if (registration_result == checkin::ReturnCode::ok)
                            {
                                registration_information = p_checkin->show_registered_vehicles();
                            }
                            else if (registration_result == checkin::ReturnCode::action_impossible)
                            {
                                current_registration_session_finished = true;
                            }
                            else
                            {
                                try_again_message = wrong_input_message;
                            }
                        }
                    }
                }
                else if (starting_action_number && action == starting_action_number)
                {
                    registration_completely_finished = true;
                }
                else
                {
                    outer_try_again_message = wrong_input_message;
                }
                
                std::system("cls");
            }
            
            p_garage->prepare_participants(p_race);
            
            bool final_action_got = false;
            while (!final_action_got)
            {
                std::string race_results = p_race->show_results();
                std::cout << saved_information << std::endl;
                std::cout << race_results << std::endl;
                
                std::cout << "1. Run another race\n";
                std::cout << "0. Quit\n";
                
                std::string user_final_action;
                std::cin >> user_final_action;
                if (user_final_action == "0")
                {
                    final_action_got = true;
                    repeat_race = false;
                }
                else if (user_final_action == "1")
                {
                    final_action_got = true;
                }
                std::system("cls");
            }
        }
    }
    catch(std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}

