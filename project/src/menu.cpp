#include "menu.h"
// menu.cpp

void run_menu(Companies &all, Company_ptr &ptr)
{
    std::vector<Stats> result;
    std::string new_name;
    size_t num;

    CompanyMenu choice;
    utils::Company_menu();
    while (true)
    {
        choice = static_cast<CompanyMenu>(utils::get_number(0, 6,"Enter a choice ([6] menu) >"));
        switch (choice)
        {

        case CompanyMenu::Exit:

            std::cout << "Exiting company!\n";
            break;

        case CompanyMenu::Update:

            if (!all.update(ptr))
                std::cout << "Error: Please wait at least 1 minute before update!\n";

            break;

        case CompanyMenu::Analyze:

            num = ptr->number_of_prices();
            num = utils::get_number(0, num, ("Enter window size (current maximum '" + std::to_string(num) + "'):"));

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

        case CompanyMenu::MaxPriceInLastNumMinutes:

            std::cout << "Enter minutes: ";
            num = utils::get_number(0, 60);
            try
            {
                size_t price = ptr->max_price_in_last_N_minutes(num);
                std::cout << "Max stock price in last '" << num << "' minutes is: " << price << "\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }

            break;

        case CompanyMenu::ClearOld:
            ptr->clean_old();
            std::cout << "Success clean up.\n";
            break;

        case CompanyMenu::Rename:
            new_name = utils::get_string("Enter new name:");
            if (all.rename_company(ptr, new_name))
                std::cout <<"Success renaming.";
            else
            std::cout << "Error: rename failed.company might not exist!\n ";
            break;

        case CompanyMenu::ShowMenu:

            utils::Company_menu();
            break;

            // debuging
            // case 7:
            //     ptr->print_maxe();
            //     break;
            // case 8:
            //     ptr->print_all();
            //     break;
        }
        if (choice == CompanyMenu::Exit)
            break;
    }
}