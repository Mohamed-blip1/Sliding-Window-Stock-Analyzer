#pragma once
// companies.h : Manages multiple companies and provides fast lookup / suggestions
#include <unordered_map>
#include <unordered_set>
#include "company.h"
#include <iostream>
#include <memory>
#include <set>

constexpr size_t EXPECTED_COMPANIES = 50; // Initial bucket count for hash map
constexpr double LOAD_FACTOR = 0.7;       // Max load factor for hash map
constexpr size_t MAX_SUGGESTIONS = 6;     // Max number of company suggestions
constexpr size_t NOT_EXIST = 0;           // Used for not-found cases

using Company_ptr = std::shared_ptr<Company>;

// Ordering comparator: sort by timestamp (newer first), break ties by name
struct Compare
{
    bool operator()(const Company_ptr &a, const Company_ptr &b) const
    {
        const auto &priceA = a->get_last_price();
        const auto &priceB = b->get_last_price();

        if (priceA.timestamp != priceB.timestamp)
            return priceA.timestamp > priceB.timestamp;

        return a->get_name() < b->get_name();
    }
};

// Container of companies with both sorted order and fast name lookup
class Companies
{
public:
    Companies() noexcept
    {
        companies_.rehash(EXPECTED_COMPANIES);
        companies_.max_load_factor(LOAD_FACTOR);
    };

    // Add a new company by name
    bool add_company(const std::string &name) noexcept;

    // Rename an existing company
    bool rename_company(const Company_ptr &ptr, const std::string &new_name) noexcept;

    // Remove a company by name
    bool remove_company(const std::string &name) noexcept;

    // Get reference to a company by name
    const Company_ptr &enter_company(const std::string &name) const;

    // Update a company’s stock price and reorder by last price
    bool update_order(const Company_ptr &ptr) noexcept;

    // Suggest the last updated companies (up to MAX_SUGGESTIONS)
    std::vector<std::string> last_updated_companies_suggestion() const noexcept;

    // Check if company exists by name
    bool check_existing(const std::string &name) const noexcept;

private:
    std::set<Company_ptr, Compare> sorted_company_by_last_price; // Ordered by recency
    std::unordered_map<std::string, Company_ptr> companies_;     // Fast name lookup
};
