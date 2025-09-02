// main.cpp
#include <iostream>
#include "company.h"
#include "utils.h"

int main()
{

    Company comp("My Company");
    size_t window_size;
    size_t choice;

    std::cout << "======= Sliding Window Stock menu =======\n";
    do
    {
        utils::menu();
        choice = utils::get_valid_number_from_user();
        switch (choice)
        {
        case 0:
            std::cout << "Goodbye!\n";
            break;
        case 1:
            try
            {
                comp.update_price();
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
            break;

        case 2:
        {
            std::vector<Stats> result;
            std::cout << "Enter window size: ";
            window_size = utils::get_valid_number_from_user();
            result.reserve(LIMITS_PRICES);
            try
            {
                result = comp.analyze_with_sliding_window(window_size);
                std::cout << "\n-----" << comp.name() << "-----\n";
                for (const auto &stats : result)
                    print(stats);
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
                size_t price = comp.max_stock_price_in_last_N_minutes(minutes);
                std::cout << "\nMax stock price in last '" << minutes << "' minutes is: " << price << "\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
        break;

        case 4:
            comp.clean_old();
            break;
        default:
            std::cout << "Please enter a valid choice!\n";
            break;
        }
    } while (choice);

    return 0;
}