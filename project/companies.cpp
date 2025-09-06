// companies.cpp
#include "companies.h"

bool Companies::check_existing(const std::string &name) const noexcept
{
    return companies_.count(name) > 0;
}

bool Companies::add_company(const std::string &name) noexcept
{
    if (check_existing(name)) // If already exist
        return false;

    auto ptr = std::make_shared<Company>(name, true);

    // Store companies sorted by last price
    auto it = sorted_company_by_last_price.lower_bound(ptr);
    sorted_company_by_last_price.emplace_hint(it, ptr);

    // Store companies in a map for quick access
    companies_.emplace(name, ptr);

    return true;
}

bool Companies::rename_company(const Company_ptr &ptr, const std::string &new_name) noexcept
{
    if (!check_existing(ptr->get_name())) // If not exist
        return false;

    // Erase then insert with new key
    companies_.erase(ptr->get_name());
    companies_.emplace(new_name, ptr);

    // Erase, rename and reinsert
    sorted_company_by_last_price.erase(ptr);
    ptr->set_name(new_name);
    sorted_company_by_last_price.insert(ptr);

    return true;
}

bool Companies::remove_company(const std::string &name) noexcept
{
    if (auto it = companies_.find(name); it != companies_.end())
    {
        sorted_company_by_last_price.erase(it->second);
        companies_.erase(it);

        return true;
    }
    return false; // if not exist
}

const Company_ptr &Companies::enter_company(const std::string &name) const
{
    auto it = companies_.find(name);
    if (it == companies_.end()) // If not exist
        throw std::runtime_error("Company does not exist!");

    // return pointer to object
    return it->second;
}

bool Companies::update_order(const Company_ptr &ptr) noexcept
{
    // Check if the period has passed
    int duration = ptr->update_time_check();
    if (duration == ONE_MINUTE_NOT_PASSED)
        return false;

    // Erase, update_price and reinsert
    sorted_company_by_last_price.erase(ptr);
    ptr->update_price();
    sorted_company_by_last_price.insert(ptr);

    return true;
}

std::vector<std::string> Companies::last_updated_companies_suggestion() const noexcept
{
    std::vector<std::string> suggestions_;
    size_t limits = std::min<size_t>(MAX_SUGGESTIONS, sorted_company_by_last_price.size());
    suggestions_.reserve(limits);

    // Store suggestions to vector
    auto it = sorted_company_by_last_price.begin();
    while (limits-- && it != sorted_company_by_last_price.end())
    {
        suggestions_.emplace_back((*it)->get_name());
        ++it;
    }

    return suggestions_;
}
