// company.h
#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>
#include <chrono>

constexpr size_t LIMITS_PRICES = 15;
constexpr size_t UPDATE_TIME = 1;  // minute
constexpr size_t LIMITS_TIME = 15; // minute
constexpr int MIN_PRICE = 100;
constexpr int MAX_PRICE = 300;

struct PricePoint
{
    std::chrono::system_clock::time_point timestamp;
    int price;
};
struct Stats
{
    int max;
    int min;
    double median;
    double average;
};

void print(const Stats &stats) noexcept;

class Company
{
public:
    using System_clock = std::chrono::system_clock;
    using Minutes = std::chrono::minutes;

public:
    Company() = default;

    Company(std::string name) noexcept;

    std::vector<Stats> analyze_with_sliding_window(size_t window_size) const;

    int max_stock_price_in_last_N_minutes(size_t minutes) const;

    void update_price();

    void clean_old() noexcept;

    const std::string &name() const noexcept;

    // debuging
    //  void print_maxe() noexcept;
    //  void print_all() noexcept;

private:
    double compute_median(const std::deque<int> &window) const noexcept;

    Stats compute_stats(const std::deque<int> &window, double sum) const noexcept;

private:
    std::string company_name_;
    std::deque<PricePoint> prices_;
    std::deque<PricePoint> max_prices_;

    std::mt19937 gen_{std::random_device{}()};
    std::uniform_int_distribution<> distrib_{MIN_PRICE, MAX_PRICE};
};