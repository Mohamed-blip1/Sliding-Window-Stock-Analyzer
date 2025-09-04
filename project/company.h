// company.h
#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>
#include <chrono>

constexpr size_t LIMITS_PRICES = 15; // Max feed price at the beginning
constexpr size_t UPDATE_TIME = 1;    // Minute. in update_price()
constexpr size_t LIMITS_TIME = 15;   // clean_old() than 15 minutes
constexpr int MIN_PRICE = 100;       // Minimum price
constexpr int MAX_PRICE = 300;       // Maximum

struct PricePoint // Store the price and time
{
    std::chrono::system_clock::time_point timestamp;
    int price;

    PricePoint(std::chrono::system_clock::time_point tp, int p) noexcept
        : timestamp(tp), price(p) {}
};
struct Stats // Store stats of the window
{
    int max;        // Maximum value
    int min;        // Minimum ...
    double median;  //...
    double average; //...
};

// Print stats of each window
void print_stats(const Stats &stats) noexcept;

class Company // Data of a company
{
public:
    using System_clock = std::chrono::system_clock;
    using Minutes = std::chrono::minutes;

public:
    Company() = default;

    // construct the company with its name
    Company(std::string name) noexcept;

    // Analyze and get the stats of every window with a User-selected window size using a sliding window technique
    [[nodiscard]] std::vector<Stats> analyze_with_sliding_window(size_t window_size) const;

    // Get max stock price with a User-selected period
    [[nodiscard]] int max_stock_price_in_last_N_minutes(size_t minutes) const;

    // Update price + Get the missing updated prices
    void update_price();

    // Clean up prices older than LIMITS_TIME (15 min)
    void clean_old() noexcept;

    // Get company name
    const std::string &name() const noexcept;

    // debuging
    // void print_maxe() noexcept;
    // void print_all() noexcept;

private:
    // Culculate the median of a window
    double compute_median(const std::deque<int> &window) const noexcept;

    // Culculate the all stats(max,min,median->{using: compute_median()},average)
    Stats compute_stats(const std::deque<int> &window, double sum) const noexcept;

private:
    std::string company_name_;
    std::deque<PricePoint> prices_;     // Store all company prices
    std::deque<PricePoint> max_prices_; // Store max values for fast access

    // Random number generator
    std::mt19937 gen_{std::random_device{}()};
    std::uniform_int_distribution<> distrib_{MIN_PRICE, MAX_PRICE};
};