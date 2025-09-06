#pragma once
// company.h : Represents a single company with its stock prices and statistics
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <deque>

// Status codes and constraints
constexpr const int ONE_MINUTE_NOT_PASSED = -1; // Returned if update is attempted too soon
constexpr const size_t LIMITS_PRICES = 15;      // Initial number of random prices to seed a company
constexpr const size_t UPDATE_TIME = 1;         // Required time (minutes) between updates
constexpr const size_t LIMITS_TIME = 15;        // Keep only data from the last 15 minutes
constexpr const int MIN_PRICE = 100;            // Min simulated stock price
constexpr const int MAX_PRICE = 300;            // Max simulated stock price

// Represents a single price point with timestamp
struct PricePoint
{
    using Time_point = std::chrono::system_clock::time_point;

    Time_point timestamp;
    int price;

    PricePoint(Time_point tp, int p) noexcept
        : timestamp(tp), price(p) {}
};

// Holds statistics of a price window
struct Stats
{
    int max;
    int min;
    double median;
    double average;
};

// Print a Stats object to console
void print_stats(const Stats &stats) noexcept;

// Represents a single company's stock data
class Company
{
public:
    using System_clock = std::chrono::system_clock;
    using Minutes = std::chrono::minutes;

public:
    Company() = default;

    // Construct a company with its name and seed with LIMITS_PRICES initial prices
    explicit Company(std::string name, bool feed_initial = true) noexcept;

    // Analyze stock prices with a sliding window of given size
    [[nodiscard]] std::vector<Stats> analyze_with_sliding_window(size_t window_size) const;

    // Return the maximum stock price observed in the last N minutes
    [[nodiscard]] int max_stock_price_in_last_N_minutes(size_t minutes) const;

    // Check how many minutes passed since last update
    // Returns ONE_MINUTE_NOT_PASSED if less than UPDATE_TIME minutes
    [[nodiscard]] int update_time_check() const noexcept;

    // Insert a new stock price with current timestamp
    void update_price() noexcept;

    // Remove old price points older than LIMITS_TIME
    void clean_old() noexcept;

    // Get / set company name
    const std::string &get_name() const noexcept;
    void set_name(const std::string &new_name) noexcept;

    // Access the last recorded price
    PricePoint &get_last_price() noexcept;

private:
    // Compute median of a window
    double compute_median(const std::deque<int> &window) const noexcept;

    // Compute full statistics (max, min, median, average) of a window
    Stats compute_stats(const std::deque<int> &window, double sum) const noexcept;

private:
    std::string company_name_;          // Company name
    std::deque<PricePoint> prices_;     // All stock prices
    std::deque<PricePoint> max_prices_; // Max prices for fast retrieval

    // Random number generator for simulated prices
    std::mt19937 gen_{std::random_device{}()};
    std::uniform_int_distribution<> distrib_{MIN_PRICE, MAX_PRICE};
};
