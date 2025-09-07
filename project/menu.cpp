#include "menu.h"
// menu.cpp

void run_menu(Companies &all, Company_ptr &ptr)
{
    size_t choice = std::numeric_limits<size_t>::max();
    std::vector<Stats> result;
    std::string new_name;
    size_t num;

    utils::Company_menu();
    while (choice != 0)
    {
        choice = utils::get_valid_number_from_user();
        switch (choice)
        {
        case 1:
            if (!all.update_order(ptr))
                std::cout << "Error: Please wait at least 1 minute before update!\n";

            break;

        case 2:
            std::cout << "Enter window size: ";
            num = utils::get_valid_number_from_user();
            try
            {
                result = ptr->analyze_with_sliding_window(num);
                std::cout << "\n-----" << ptr->get_name() << "-----\n";
                num = 0;
                for (const auto &stats : result)
                {
                    std::cout << "\nWindow #" << ++num << ":\n";
                    print_stats(stats);
                }
                std::cout << "\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }

            break;

        case 3:

            std::cout << "Enter minutes: ";
            num = utils::get_valid_number_from_user();
            try
            {
                size_t price = ptr->max_stock_price_in_last_N_minutes(num);
                std::cout << "\nMax stock price in last '" << num << "' minutes is: " << price << "\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }

            break;

        case 4:
            ptr->clean_old();
            std::cout << "Success clean up.\n";
            break;

        case 5:
            new_name = utils::get_valid_string_from_user("Enter new name:");
            if (!all.rename_company(ptr, new_name))
                std::cout << "Error: rename failed.company might not exist.\n ";
            break;

        case 9:
            utils::Company_menu();
            break;

            // debuging
            // case 5:
            //     ptr->print_maxe();
            //     break;
            // case 6:
            //     ptr->print_all();
            //     break;

        case 0:
            std::cout << "Exiting company!\n";
            break;

        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
}