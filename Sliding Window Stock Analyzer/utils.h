#include <iostream>

namespace utils
{
    void menu()
    {
        std::cout << "\nMenu:\n";
        std::cout << "1 - Reload prices\n";
        std::cout << "2 - Sliding window\n";
        std::cout << "3 - Max stock price in last N minutes\n";
        std::cout << "4 - Clean old prices\n";
    }
}