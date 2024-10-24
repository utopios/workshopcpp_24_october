#include <iostream>
#include <algorithm>
#include <execution>
#include <cstdint>
#include <random>
#include <vector>
#include <chrono>

using namespace std::chrono;

void exercise1(auto policy, std::vector<uint64_t>& v)
{
    std::for_each(policy, std::begin(v), std::end(v), [](auto& n) { n *= n; });
}

void exercise2(auto policy, std::vector<uint64_t>& v)
{
    std::sort(policy, std::begin(v), std::end(v));
}

struct StopWatch {
    StopWatch(const std::string& name) : start { high_resolution_clock::now() }, name {name} {}
    ~StopWatch() {
        std::cout << "*** " << name << " **** : " <<
                  duration_cast<std::chrono::microseconds>( high_resolution_clock::now()- start) <<
                  " ms" << std::endl;
    }

    std::string name;
    time_point<system_clock> start;
};
int main()
{
    std::vector<uint64_t> v(10'000'000);
    std::mt19937 gen {std::random_device{}()};
    std::ranges::generate(v, gen);

    {
        StopWatch {"parallel for_each"};
        exercise1(std::execution::par, v);
    }
    {
        StopWatch {"sequential for_each"};
        exercise1(std::execution::seq, v);
    }


    {
        StopWatch {"parallel sort"};
        exercise2(std::execution::par, v);
    }
    {
        StopWatch {"sequential sort"};
        exercise2(std::execution::seq, v);
    }
}
