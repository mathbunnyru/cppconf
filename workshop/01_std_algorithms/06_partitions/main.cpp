
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>


int main(int argc, char *argv[])
{
    std::vector<int> xs { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

    const auto first_end =
        std::stable_partition(std::begin(xs), std::end(xs),
                              [] (auto i) { return i % 3 == 0; }
                );

    const auto second_end =
        std::stable_partition(first_end, std::end(xs),
                              [] (auto i) { return i % 3 == 1; }
                );

    std::copy(std::begin(xs), std::end(xs),
              std::ostream_iterator<int>(std::cout, " "));

    return 0;
}
