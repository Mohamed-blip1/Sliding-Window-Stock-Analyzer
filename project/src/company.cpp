// company.cpp
#include "company.h"
#include <iostream>
#include <iomanip>

void print_stats(const Stats &stats) noexcept
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Max: " << stats.max << "\n";
    std::cout << "Min: " << stats.min << "\n";
    std::cout << "Med: " << stats.median << "\n";
    std::cout << "Avg: " << stats.average << "\n";
}

// debuging
// void Company::print_maxe() noexcept
// {
//     for (size_t i = 0; i < max_prices_.size(); ++i)
//     {
//         std::cout << "#" << i << "\n";
//         std::cout << "Price: " << max_prices_[i].price << "\n";
//         auto t = std::chrono::system_clock::to_time_t(max_prices_[i].timestamp);
//         std::cout << "Time: " << std::ctime(&t) << " : " << max_prices_[i].price << "\n";
//     }
//     std::cout << "\n------size: " << max_prices_.size() << "---------\n";
// }
// void Company::print_all() noexcept
// {
//     for (size_t i = 0; i < prices_.size(); ++i)

//     {
//         std::cout << "#" << i << "\n";
//         std::cout << "Price: " << prices_[i].price << "\n";
//         auto t = std::chrono::system_clock::to_time_t(prices_[i].timestamp);
//         std::cout << "Time: " << std::ctime(&t) << " : " << prices_[i].price << "\n";
//     }
//     std::cout << "\n------size: " << prices_.size() << "---------\n";
// }

// feed prices
Company::Company(std::string name, bool feed_initial) noexcept
    : company_name_(std::move(name))
{
    if (feed_initial)
        for (size_t i = 0; i < LIMITS_PRICES; ++i)
        {
            auto timestamp = System_clock::now() - Minutes(LIMITS_PRICES - 1 - i);
            auto price = distrib_(gen_);

            while (!max_prices_.empty() &&
                   price > max_prices_.back().price)
                max_prices_.pop_back();

            max_prices_.emplace_back(timestamp, price);
            prices_.emplace_back(timestamp, price);
        }
}

std::vector<Stats> Company::analyze_with_sliding_window(size_t window_size) const
{
    if (!window_size)
        throw std::runtime_error("No window with size 0!");
    if (prices_.empty())
        throw std::runtime_error("No prices yet!");
    if (window_size > prices_.size())
        throw std::runtime_error("Max window size: '" + std::to_string(prices_.size()) + "'!");

    std::vector<Stats> all_stats;
    std::deque<int> window;
    int current_price;
    double sum = 0;

    all_stats.reserve(prices_.size() - window_size + 1);
    for (size_t i = 0; i < prices_.size(); ++i)
    {
        current_price = prices_[i].price;
        sum += current_price;
        window.push_back(current_price);

        if (window.size() == window_size)
        {
            all_stats.emplace_back(compute_stats(window, sum));

            sum -= window.front();
            window.pop_front();
        }
    }

    return all_stats;
}

int Company::max_price_in_last_N_minutes(size_t minutes) const
{
    if (prices_.empty())
        throw std::runtime_error("No prices yet!");

    auto now = System_clock::now();
    auto cutoff = now - Minutes(minutes);

    if (prices_.back().timestamp < cutoff)
        throw std::runtime_error("There is no Data in the last: " + std::to_string(minutes) + " min!");

    for (auto it = max_prices_.begin(); it != max_prices_.end(); ++it)
        if (it->timestamp >= cutoff) // if 'timestamp' equal or newar to minutes
            return it->price;

    throw std::runtime_error("No data found in time range!");
}

int Company::update_time_check() const noexcept
{
    auto now = System_clock::now();
    // shold get fixed with not feeding at the beginig
    if (prices_.empty())
        return ONE_MINUTE_NOT_PASSED;

    int duration = static_cast<int>(std::chrono::duration_cast<Minutes>(now - prices_.back().timestamp).count());
    if (duration < UPDATE_TIME)
        return ONE_MINUTE_NOT_PASSED;

    return duration;
}

void Company::update_price() noexcept
{
    auto timestamp = System_clock::now();
    auto price = distrib_(gen_);

    while (!max_prices_.empty() && price > max_prices_.back().price)
        max_prices_.pop_back();

    max_prices_.emplace_back(timestamp, price);
    prices_.emplace_back(timestamp, price);
}

void Company::clean_old() noexcept
{
    auto now = System_clock::now();
    auto time_limits = now - Minutes(LIMITS_TIME);

    // Let 1 price for sorting in companies.(cpp/h)
    while (prices_.size() > 1 && prices_.front().timestamp < time_limits)
        prices_.pop_front();

    while (max_prices_.size() > 1 && max_prices_.front().timestamp < time_limits)
        max_prices_.pop_front();
}

const std::string &Company::get_name() const noexcept { return company_name_; }
void Company::set_name(const std::string &new_name) noexcept { company_name_ = new_name; }

PricePoint &Company::get_last_price() noexcept { return prices_.back(); };

double Company::compute_median(const std::deque<int> &window) const noexcept
{
    std::vector<int> sorted_window{window.begin(), window.end()};
    std::sort(sorted_window.begin(), sorted_window.end());
    size_t n = sorted_window.size();

    if (n % 2 != 0)
        return sorted_window[n / 2];
    else
        return (sorted_window[n / 2] + sorted_window[(n / 2) - 1]) / 2.0;
}

Stats Company::compute_stats(const std::deque<int> &window, double sum) const noexcept
{
    Stats stats;
    stats.max = *std::max_element(window.begin(), window.end());
    stats.min = *std::min_element(window.begin(), window.end());
    stats.median = compute_median(window);
    stats.average = sum / window.size();
    return stats;
}
