#include <iostream>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/algorithm/any_of.hpp>

using namespace ranges::v3;

template <typename F>
auto to_pair_function(F f) {
    return [f] (const auto &pair) {
        return f(pair.first, pair.second);
    };
}

template <typename Range>
bool is_sorted(const Range &rng)
{
    return !any_of(view::zip(rng, view::tail(rng)), to_pair_function(std::greater<>()));
}


int main(int argc, char *argv[])
{
    std::string colour = "Hooloovoo";
    std::string word = "Almost";

    std::cerr << colour << ": " << is_sorted(colour) << std::endl;
    std::cerr << word << ": " << is_sorted(word) << std::endl;

}
