// utils.cpp
#include "utils.h"
#include <string>

std::string trim(const std::string &str, char target)
{
    size_t start = str.find_first_not_of(target);
    size_t end = str.find_last_not_of(target);

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

namespace utils
{
    void menu() noexcept
    {
        constexpr const size_t space = 3;

        std::cout << "\nMenu:\n";
        std::cout << std::left << std::setw(space) << "1" << "- Add company\n";
        std::cout << std::left << std::setw(space) << "2" << "- Enter company\n";
        std::cout << std::left << std::setw(space) << "3" << "- Companies suggestions\n";
        std::cout << std::left << std::setw(space) << "4" << "- Delete Company\n";
        std::cout << std::left << std::setw(space) << "9" << "- Menu\n";
        std::cout << std::left << std::setw(space) << "0" << "- Exit\n";
    }

    void Company_menu() noexcept
    {
        constexpr const size_t space = 3;

        std::cout << "\nMenu:\n";
        std::cout << std::left << std::setw(space) << "1" << "- Reload prices\n";
        std::cout << std::left << std::setw(space) << "2" << "- Analyze with sliding window\n";
        std::cout << std::left << std::setw(space) << "3" << "- Max price in last N minutes\n";
        std::cout << std::left << std::setw(space) << "4" << "- Clean old prices\n";
        std::cout << std::left << std::setw(space) << "5" << "- Rename a company\n";
        std::cout << std::left << std::setw(space) << "9" << "- Menu\n";
        std::cout << std::left << std::setw(space) << "0" << "- Exit company\n";
    }

    std::string get_valid_string_from_user(const std::string &UI) noexcept
    {
        std::string name;
        do
        {
            std::cout << UI;
            std::getline(std::cin, name);
            name = trim(name);
            if (name.empty())
                std::cout << "Input cannot be empty. Please try again.\n";

        } while (name.empty());

        return name;
    }

    size_t get_valid_number_from_user() noexcept
    {
        size_t number;
        while (true)
        {
            std::cout << "> ";
            std::cin >> number;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(INPUT_BUFFER_SIZE, '\n');
                std::cout << "\nPlease Enter A Valid Number: ";
            }
            else
            {
                std::cin.ignore(INPUT_BUFFER_SIZE, '\n');
                return number;
            }
        }
    }

}