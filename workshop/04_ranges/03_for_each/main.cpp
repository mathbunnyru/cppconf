#include <iostream>
#include <vector>
#include <functional>
#include <range/v3/view.hpp>

using namespace ranges::v3;
using namespace std::placeholders;

int main(int argc, char *argv[])
{
    std::vector<int> xs = { -1, -3, -5, 1, 3, 5};

    // Getting absolute values of xs, filtering them,
    // and converting to strings
    auto results =
        xs | view::transform(abs)
           | view::filter(std::bind(std::less<>(), _1, 6))
           | view::transform([] (auto value) { return std::to_string(value); });

    // Before C++17, this will require RANGE_FOR macro instead
    for (auto value: results) {
        std::cout << value << std::endl;
    }

    return 0;
}
