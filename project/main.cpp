//  Run (in terminal): cd path (...\Sliding-Window-Stock-Analyzer\project)
//                     then: g++ -std=c++17 main.cpp menu.cpp companies.cpp company.cpp utils.cpp -o main.exe
/*                                       \ or your compaler version                                     \ or name it somthing else      */
//                     then: ./main.exe
// main.cpp : Entry point for Sliding Window Stock program
#include <iostream>
#include "menu.h"

int main()
{
    size_t choice = std::numeric_limits<size_t>::max();
    std::vector<std::string> suggestions;
    std::string name;
    Company_ptr ptr;
    Companies all;
    size_t index;

    std::cout << "\n======= Sliding Window Stock Menu =======\n";
    utils::menu();

    while (choice != 0)
    {
        choice = utils::get_valid_number_from_user();
        switch (choice)
        {
        case 1:
            // Add a company
            name = utils::get_valid_string_from_user("Enter company name:");
            if (!all.add_company(name))
                std::cout << "Company already exists!\n";
            break;

        case 2:
            // Enter a specific company
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
            run_menu(all, ptr);
            break;

        case 3:
            // Show last updated companies
            suggestions = all.last_updated_companies_suggestion();
            if (suggestions.empty())
            {
                std::cout << "No Companies yet!\n";
                break;
            }
            index = 1;
            for (const auto &name : suggestions)
                std::cout << std::left << std::setw(2) << index++ << "- " << name << "\n";
            break;

        case 4:
            // Remove a company
            name = utils::get_valid_string_from_user("Enter company name:");
            if (!all.remove_company(name))
                std::cout << "Company not found!\n";
            else
                std::cout << "Company deletion successful!\n";
            break;

        case 9:
            // Print menu again
            utils::menu();
            break;

        case 0:
            std::cout << "Exiting program!\n";
            break;

        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
    return 0;
}
