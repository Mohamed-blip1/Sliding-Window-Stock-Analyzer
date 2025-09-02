// utils.h
#pragma once
#include <iostream>
#include <iomanip>
#include <algorithm>

std::string trim(const std::string &str, char target = ' ')
{
    size_t start = str.find_first_not_of(target);
    size_t end = str.find_last_not_of(target);

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

namespace utils
{
    inline std::string get_valid_string_from_user(const std::string &UI) noexcept
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

    void menu()
    {
        constexpr size_t space = 3;

        std::cout << "\nMenu:\n";
        std::cout << std::setw(space) << "1" << std::left << "- Reload prices\n";
        std::cout << std::setw(space) << "2" << std::left << "- Sliding window\n";
        std::cout << std::setw(space) << "3" << std::left << "- Max stock price in last N minutes\n";
        std::cout << std::setw(space) << "4" << std::left << "- Clean old prices\n";
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
                std::cin.ignore(1000, '\n');
                std::cout << "\nPlease Enter A Valid Number: ";
            }
            else
            {
                std::cin.ignore(1000, '\n');
                return number;
            }
        }
    }

}