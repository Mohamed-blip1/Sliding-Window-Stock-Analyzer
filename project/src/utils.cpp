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
        std::cout << std::left << std::setw(space) << "0" << "- Exit company\n";
    }

    std::string get_string(const std::string &ui) noexcept
    {
        std::string name;
        do
        {
            std::cout << ui;
            std::getline(std::cin, name);
            name = trim(name);
            if (name.empty())
                std::cout << "Input cannot be empty. Please try again.\n";

        } while (name.empty());

        return name;
    }

size_t get_number(int min, int max, const std::string &ui) noexcept
    {
        size_t number;
        std::string num_str;

        if (min > max)
            std::swap(min, max);

        while (true)
        {
            num_str = get_string(ui);

            if (num_str.empty())
            {
                std::cout << "Empty Input!\n";
                continue;
            }

            std::istringstream iss(num_str);
            if (iss >> number && iss.eof())
                if (number >= min && number <= max)
                    return number;

            std::cout << "'" << num_str << "' Not valid number\n";
            continue;
        }
    }

}