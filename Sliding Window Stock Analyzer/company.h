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

void print(const Stats &stats) noexcept
{
    std::cout << "\n";
    std::cout << "Max: " << stats.max << "\n";
    std::cout << "Min: " << stats.min << "\n";
    std::cout << "Med: " << stats.median << "\n";
    std::cout << "Avg: " << stats.average << "\n";
}

class Company
{
public:
    using System_clock = std::chrono::system_clock;
    using Minutes = std::chrono::minutes;

public:
    Company() = default;

    Company(const std::string &name) noexcept
        : company_name_(name)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution distrib(MIN_PRICE, MAX_PRICE);

        PricePoint point;
        for (size_t i = 0; i < LIMITS_PRICES; ++i)
        {
            auto now = System_clock::now();
            point.timestamp = now - Minutes(LIMITS_PRICES - 1 - i);
            point.price = distrib(gen);
            prices_.push_back(point);
        }
    }

    std::vector<Stats> analyze_with_sliding_window(size_t window_size) const
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

    int max_stock_price_in_last_N_minutes(size_t minutes) const noexcept
    {
        auto now = System_clock::now();
        auto cutoff = now - Minutes(minutes);

        int max = prices_.back().price;
        for (auto it = prices_.rbegin(); it != prices_.rend(); ++it)
        {
            if (it->timestamp < cutoff)
                break;
            max = std::max(it->price, max);
        }
        return max;
    }

    void update_price()
    {
        auto now = System_clock::now();
        double duration = std::chrono::duration_cast<Minutes>(now - prices_.back().timestamp).count();

        if (duration < UPDATE_TIME)
            throw std::runtime_error("Please wait a few seconds and then reload!");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution distribut(MIN_PRICE, MAX_PRICE);

        PricePoint point;
        point.timestamp = System_clock::now();
        point.price = distribut(gen);
        prices_.push_back(point);
    }

    void clean_old() noexcept
    {
        auto now = System_clock::now();
        auto time_limits = now - Minutes(LIMITS_TIME);
        while (!prices_.empty() && prices_.front().timestamp < time_limits)
        {
            prices_.pop_front();
        }
    }

    const std::string &name() const noexcept { return company_name_; }

private:
    double compute_median(const std::deque<int> &window) const noexcept
    {
        std::vector<int> sorted_window;
        sorted_window.reserve(window.size());

        for (const auto &elem : window)
            sorted_window.push_back(elem);
        std::sort(sorted_window.begin(), sorted_window.end());

        size_t n = sorted_window.size();
        if (n % 2 == 0)
            return (sorted_window[(n / 2) - 1] + sorted_window[n / 2]) / 2.0;
        else
            return sorted_window[n / 2];
    }

    Stats compute_stats(const std::deque<int> &window, double sum) const noexcept
    {
        Stats stats;
        stats.max = *std::max_element(window.begin(), window.end());
        stats.min = *std::min_element(window.begin(), window.end());
        stats.median = compute_median(window);
        stats.average = sum / window.size();
        return stats;
    }

private:
    std::string company_name_;
    std::deque<PricePoint> prices_;
};