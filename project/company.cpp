// company.cpp
#include <iostream>
#include <iomanip>
#include "company.h"

void print(const Stats &stats) noexcept
{
    std::cout << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Max: " << stats.max << "\n";
    std::cout << "Min: " << stats.min << "\n";
    std::cout << "Med: " << stats.median << "\n";
    std::cout << "Avg: " << stats.average << "\n";
}

Company::Company(std::string name) noexcept
    : company_name_(std::move(name))
{

    PricePoint point;
    for (size_t i = 0; i < LIMITS_PRICES; ++i)
    {
        prices_.push_back(
            {System_clock::now() - Minutes(LIMITS_PRICES - 1 - i),
             distrib_(gen_)});
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
    double sum = 0;
    int current_price;

    for (size_t i = 0; i < prices_.size(); i++)
    {
        current_price = prices_[i].price;
        sum += current_price;
        window.push_back(current_price);

        if (window.size() == window_size)
        {
            all_stats.push_back(compute_stats(window, sum));

            sum -= window.front();
            window.pop_front();
        }
    }

    return all_stats;
}

int Company::max_stock_price_in_last_N_minutes(size_t minutes) const
{

    if (prices_.empty())
        throw std::runtime_error("No prices yet!");

    auto now = System_clock::now();
    auto cutoff = now - Minutes(minutes);

    if (prices_.back().timestamp < cutoff)
        throw std::runtime_error("There is no Data in the last: " + std::to_string(minutes) + " min!");

    int max = prices_.back().price;
    for (auto it = prices_.rbegin(); it != prices_.rend(); ++it)
    {
        if (it->timestamp < cutoff)
            break;
        max = std::max(it->price, max);
    }
    return max;
}

void Company::update_price()
{
    auto now = System_clock::now();
    double duration = std::chrono::duration_cast<Minutes>(now - prices_.back().timestamp).count();

    if (duration < UPDATE_TIME)
        throw std::runtime_error("Please wait at least 1 minute before update!");

    PricePoint point;
    for (size_t i = 0; i < (int)duration; i++)
    {
        prices_.push_back(
            {System_clock::now() - Minutes((int)duration - 1 - i),
             distrib_(gen_)});
    }
}

void Company::clean_old() noexcept
{
    auto now = System_clock::now();
    auto time_limits = now - Minutes(LIMITS_TIME);
    while (!prices_.empty() && prices_.front().timestamp < time_limits)
    {
        prices_.pop_front();
    }
}

const std::string &Company::name() const noexcept { return company_name_; }

double Company::compute_median(const std::deque<int> &window) const noexcept
{
    std::vector<int> sorted_window{window.begin(), window.end()};
    std::sort(sorted_window.begin(), sorted_window.end());

    size_t n = sorted_window.size();
    if (n % 2 == 0)
        return (sorted_window[(n / 2) - 1] + sorted_window[n / 2]) / 2.0;
    else
        return sorted_window[n / 2];
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
