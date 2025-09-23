//  Run (in terminal): cd path (...\Sliding-Window-Stock-Analyzer\project)
//                     then: g++ -std=c++17 main.cpp menu.cpp companies.cpp company.cpp utils.cpp -o main.exe
/*                                       \ or your compaler version                                     \ or name it somthing else      */
//                     then: ./main.exe
// main.cpp : Entry point for Sliding Window Stock program
#include <iostream>
#include "utils.h"
#include "menu.h"
#include <vector>

enum class Menu : size_t
{
    Exit = 0,
    AddCompany,
    EnterCompany,
    LastUpdatedCompaniesSuggestion,
    RemoveCompany,
    ShowMenu
};

int main()
{
    std::vector<std::string> suggestions;
    std::string name;
    Company_ptr ptr;
    Companies all;
    size_t index;

    std::cout << "\n======= Sliding Window Stock Menu =======\n";
    utils::menu();

    Menu choice;
    while (true)
    {
        choice = static_cast<Menu>(utils::get_number(0, 5, "Enter a choice ([5] menu) >"));
        switch (choice)
        {
        case Menu::Exit:

            std::cout << "Exiting program!\n";
            break;

        case Menu::AddCompany:

            name = utils::get_string("Enter company name: ");
            if (!all.add_company(name))
                std::cout << "Company already exists!\n";
            else
                std::cout << "Success adding.\n";
            break;

        case Menu::EnterCompany:

            try
            {
                std::string name = utils::get_string("Enter company name: ");
                ptr = all.enter_company(name);
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
                break;
            }
            run_menu(all, ptr);
            break;

        case Menu::LastUpdatedCompaniesSuggestion:

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

        case Menu::RemoveCompany:

            name = utils::get_string("Enter company name:");
            if (!all.remove_company(name))
                std::cout << "Company not found!\n";
            else
                std::cout << "Company deletion successful!\n";
            break;

        case Menu::ShowMenu:
            utils::menu();
            break;

        default:
            std::cout << "Invalid choice!\n";
            break;
        }
        if (choice == Menu::Exit)
            break;
    }
    return 0;
}
