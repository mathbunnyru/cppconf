
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

// #include <execution_policy> // c++17
#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/include/parallel_numeric.hpp>
#include <hpx/include/parallel_algorithm.hpp>
#include <hpx/parallel/algorithms/fill.hpp>

#define std_par hpx::parallel

template <typename T>
auto avg_manual(const T &xs)
{
    int result = 0;

    for (auto &&x: xs) {
        result += x;
    }

    return result / (float) xs.size();
}

template <typename T>
auto length(const T &xs)
{
    return std::distance(std::begin(xs), std::end(xs));
}

template <typename T>
auto avg_accumulate(const T &xs)
{
    return std::accumulate(std::begin(xs), std::end(xs), 0)
           / (float) length(xs);

    // Alternatively, instead of using pairs of iterators, one
    // can use a 3rd party library like boost or range-v3
    // to get the accumulate algorithm that takes a collection:
    //
    // return boost::accumulate(xs, 0) / (float) length(xs);
}

template <typename T>
auto avg_reduce(const T &xs)
{
    using std_par::reduce;
    using namespace std_par::execution;

    // c++17
    return reduce(seq, // par ...
                  std::begin(xs), std::end(xs),
                  0) / (float) length(xs);
}


int main(int argc, char *argv[])
{
    std::vector<int> xs { 1, 2, 3, 4, 5, 6, 7, 8 };

    std::cout << avg_manual(xs) << std::endl;
    std::cout << avg_accumulate(xs) << std::endl;
    std::cout << avg_reduce(xs) << std::endl;

    return 0;
}
