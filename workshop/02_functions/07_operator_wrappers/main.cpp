
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>

#include <boost/phoenix/phoenix.hpp>

template <typename Collection, typename Predicate>
void output_if(const Collection &c, Predicate p)
{
    std::copy_if(std::begin(c), std::end(c),
            std::ostream_iterator<
                    typename Collection::value_type
                >(std::cout, "\n"),
            p);
}


int main(int argc, char *argv[])
{
    // Standard library

    std::vector<int> items {
        1, 2, 3, 4, 5, 6
        };

    std::cout
        << std::accumulate(std::cbegin(items), std::cend(items),
                           1,
                           std::multiplies<int>()
                )
        << std::endl;

    std::sort(std::begin(items), std::end(items), std::greater<int>());


    // Boost.Phoenix

    using namespace boost::phoenix::placeholders;

    std::cout
        << std::accumulate(std::cbegin(items), std::cend(items),
                           1,
                           arg1 * arg2
                )
        << std::endl;

    std::sort(std::begin(items), std::end(items), arg1 > arg2);

    output_if(items, arg1 > 2);


    return 0;
}

