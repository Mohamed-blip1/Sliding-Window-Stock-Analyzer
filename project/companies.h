#pragma once
// companies.h
#include <unordered_map>
#include <unordered_set>
#include "company.h"
#include <iostream>
#include <memory>
#include <set>

const constexpr size_t EXPECTED_COMPANIES = 50;
const constexpr double LOAD_FACTOR = 0.7;
const constexpr size_t MAX_SUGGESTIONS = 6;
const constexpr size_t NOT_EXIST = 0;

using Company_ptr = std::shared_ptr<Company>;

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

class Companies
{
public:
    Companies() noexcept
    {
        companies_.rehash(EXPECTED_COMPANIES);
        companies_.max_load_factor(LOAD_FACTOR);
    };

    bool add_company(const std::string &name) noexcept;
    
    bool rename_company(const Company_ptr &ptr, const std::string &new_name) noexcept;
    
    bool remove_company(const std::string &name) noexcept;
    
    const Company_ptr &enter_company(const std::string &name) const;

    bool update_order(const Company_ptr &ptr) noexcept;

    std::vector<std::string> last_updated_companies_suggestion() const noexcept;

    bool check_existing(const std::string &name) const noexcept;

private:
    std::set<Company_ptr, Compare> sorted_company_by_last_price;
    std::unordered_map<std::string, Company_ptr> companies_;
};
