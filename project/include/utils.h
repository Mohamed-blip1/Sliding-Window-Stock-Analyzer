
#pragma once
// utils.h : Utility helpers for input validation and menus
#include <iostream>
#include <iomanip>
#include <fstream>

// Maximum buffer size for user input cleanup
constexpr int INPUT_BUFFER_SIZE = 1000;

// Trim leading and trailing characters (default: space) from a string
std::string trim(const std::string &str, char target = ' ');

namespace utils
{
    // Print the main menu (manages all companies)
    void menu() noexcept;

    // Print the company-specific submenu (operations on a single company)
    void Company_menu() noexcept;

    // Prompt user with a message, return a valid non-empty string
    std::string get_string(const std::string &ui) noexcept;

    // Prompt user until a valid number is entered
    size_t get_number(int min,int max,const std::string&ui="Enter a choice >") noexcept;
}
