#pragma once
// menu.h : Runs the interactive menu for a single company
#include "companies.h"
#include "utils.h"

enum class CompanyMenu : size_t
{
    Exit = 0,
    Update,
    Analyze,
    MaxPriceInLastNumMinutes,
    ClearOld,
    Rename,
    ShowMenu
};

// Handles the company-specific menu operations
void run_menu(Companies &all, Company_ptr &ptr);