// main.cpp
#include <iostream>
#include "companies.h"
#include "utils.h"

int main()
{
    Companies all;
    size_t window_size;
    size_t choice = -1;
    size_t choice2 = -1;

    std::cout << "\n======= Sliding Window Stock menu =======\n";
    utils::menu();
    while (choice != 0)
    {
        choice = utils::get_valid_number_from_user();
        switch (choice)
        {
        case 0:
            std::cout << "Exiting program!\n";
            break;
        case 1:
        {
            std::string name = utils::get_valid_string_from_user("Enter company name:");
            if (!all.add_company(name))
                std::cout << "Company already exist!\n";
            break;
        }

        case 3:
        {
            std::vector<std::string> suggestions = all.last_updated_companies_suggestion();

            if (suggestions.empty())
            {
                std::cout << "No Companies yet!\n";
                break;
            }

            size_t index = 1;
            for (const auto &name : suggestions)
                std::cout << std::left << std::setw(2) << index++ << "- "
                          << name << "\n";

            break;
        }
        case 4:
        {
            std::string name = utils::get_valid_string_from_user("Enter company name:");
            if (!all.remove_company(name))
                std::cout << "Company name not exist!\n";
            else
                std::cout << "Company deletion success!\n";
            break;
        }
        case 9:
            utils::menu();
            break;

        case 2:
        {
            std::shared_ptr<Company> ptr;

            try
            {
                std::string name = utils::get_valid_string_from_user("Enter company name: ");
                ptr = all.enter_company(name);
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
                break;
            }
            choice2 = -1;
            utils::Company_menu();
            while (choice2 != 0)
            {
                choice2 = utils::get_valid_number_from_user();

                switch (choice2)
                {
                case 1:
                    if (!all.update_order(ptr))
                        std::cout << "Error: Please wait at least 1 minute before update!\n";

                    break;
                case 2:
                {
                    std::vector<Stats> result;
                    std::cout << "Enter window size: ";
                    window_size = utils::get_valid_number_from_user();
                    try
                    {
                        result = ptr->analyze_with_sliding_window(window_size);
                        std::cout << "\n-----" << ptr->get_name() << "-----\n";
                        size_t i = 0;
                        for (const auto &stats : result)
                        {
                            std::cout << "\nWindow #" << ++i << ":\n";
                            print_stats(stats);
                        }
                        std::cout << "\n";
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                }
                break;
                case 3:
                {
                    size_t minutes;
                    std::cout << "Enter minutes: ";
                    minutes = utils::get_valid_number_from_user();
                    try
                    {
                        size_t price = ptr->max_stock_price_in_last_N_minutes(minutes);
                        std::cout << "\nMax stock price in last '" << minutes << "' minutes is: " << price << "\n";
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                }
                break;
                case 4:
                    ptr->clean_old();
                    std::cout << "Success clean up.\n";
                    break;
                case 5:
                {
                    std::string new_name = utils::get_valid_string_from_user("Enter new name:");
                    if (!all.rename_company(ptr, new_name))
                        std::cout << "Error: In Companies::rename_caompany.";
                    break;
                }
                case 9:
                    utils::Company_menu();
                    break;
                case 0:
                    std::cout << "Exiting company!\n";
                    break;

                    // debuging
                    // case 5:
                    //     ptr->print_maxe();
                    //     break;
                    // case 6:
                    //     ptr->print_all();
                    //     break;

                default:
                    std::cout << "Invalid choice!\n";
                    break;
                }
            }
            break;
        }
        }
    }
    return 0;
}
