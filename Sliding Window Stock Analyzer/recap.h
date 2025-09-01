#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>
#include <ctime>
#include <chrono>

constexpr size_t LIMITS_PRICES = 15;
constexpr int MIN_PRICE = 100;
constexpr int MAX_PRICE = 300;

struct Stats
{
    int max;
    int min;
    double median;
    double average;
};

void print(const Stats &stats)
{
    std::cout << "Max: " << stats.max << "\n";
    std::cout << "Min: " << stats.min << "\n";
    std::cout << "Med: " << stats.median << "\n";
    std::cout << "Avg: " << stats.average << "\n\n";
}

class Company
{
public:
    Company() = default;

    Company(const std::string &name) noexcept
        : company_name_(name)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution distrib(MIN_PRICE, MAX_PRICE);

        time_t current_time;
        std::time(&current_time);

        for (size_t i = 0; i < LIMITS_PRICES; ++i)
        {
            auto time = std::chrono::system_clock::now();
            prices_.push_back(distrib(gen));
        }
    }

    std::vector<Stats> analyze_with_sliding_window(size_t window_size) const
    {
        if (prices_.empty())
            throw std::runtime_error("No prices yet!");

        if (window_size > prices_.size())
            throw std::runtime_error("Maximum window size is: " + std::to_string(LIMITS_PRICES) + "!");

        std::vector<Stats> all_stats;
        std::deque<int> window;
        double sum = 0;
        int current_price;

        for (size_t i = 0; i < prices_.size(); i++)
        {
            current_price = prices_[i];

            if (window.size() == window_size)
            {
                all_stats.push_back(compute_stats(window, sum));

                sum -= window.front();
                window.pop_front();
            }
            sum += current_price;
            window.push_back(current_price);
        }

        return all_stats;
    }

    const std::string &name() const noexcept { return company_name_; }

private:
    double compute_median(const std::deque<int> &window) const noexcept
    {
        std::deque<int> sorted_window = window;
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
    std::deque<int> prices_;
};