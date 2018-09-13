#include <iostream>
#include <vector>
#include <range/v3/view.hpp>

using namespace ranges::v3;

template <typename Range>
int count_adj_equals(const Range &rng)
{
    return accumulate(
        view::zip(rng, view::tail(rng)) | view::transform([] (const auto &pair) {
                    return pair.first == pair.second ? 1 : 0;
                 })
        , 0);
}


int main(int argc, char *argv[])
{
    std::string colour = "Hooloovoo";

    std::cerr << colour << ": " << count_adj_equals(colour) << std::endl;

}
