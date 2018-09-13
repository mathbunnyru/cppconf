
#include <vector>
#include <numeric>
#include <iostream>

// In C++17 and earlier, accumulate is pessimised to perform copies
// of the accumulator value all the time. In C++20 it should be
// optimized in a similar way to the following:
template <typename ItBegin, typename ItEnd, typename Init, typename Func>
Init moving_accumulate(ItBegin begin, ItEnd end, Init acc, Func func)
{
    for (; begin != end; ++begin) {
        acc = func(std::move(acc, *begin));
    }

    return std::move(acc);
}

std::string append_if_odd(const std::string &acc, int x)
{
    return x % 2 != 0 ?
            (acc + std::to_string(x)) : acc;
}

int main(int argc, char *argv[])
{
    std::vector<int> xs { 1, 2, 3, 4, 5 };

    std::cout << std::accumulate(std::cbegin(xs), std::cend(xs),
                                 std::string(),
                                 append_if_odd) << std::endl;

    return 0;
}

