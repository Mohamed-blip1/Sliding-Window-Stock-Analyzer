// utils.h
#pragma once
#include <iostream>
#include <iomanip>

namespace utils
{
    void menu()
    {
        constexpr size_t space = 3;

        std::cout << "\nMenu:\n";
        std::cout << std::left << std::setw(space) << "1" << "- Reload prices\n";
        std::cout << std::left << std::setw(space) << "2" << "- Sliding window\n";
        std::cout << std::left << std::setw(space) << "3" << "- Max stock price in last N minutes\n";
        std::cout << std::left << std::setw(space) << "4" << "- Clean old prices\n";
        std::cout << std::left << std::setw(space) << "0" << "- exit\n";
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