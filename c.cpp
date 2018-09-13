#include <numeric>
#include <vector>
#include <iostream>
#include <range/v3/action.hpp>
#include <range/v3/istream_range.hpp>
#include <range/v3/view.hpp>

using namespace ranges::v3;

// void simple_example() {
//   std::vector<int> xs { 1, 2, 3, 4 };

//   accumulate(
//     view::filter(xs, [](int x) { return x > 3; }), 0
//   );

//   equal(xs, view::reverse(xs));

//   filter(transform(filter(xs, p1), trafo), p2)

//   xs | view::filter(p1)
//      | view::transform(trafo)
//      | view::filter(p2);
// }

std::string string_to_lower(const std::string& s) {
  return s | view::transform(tolower);
}

std::string string_only_alnum(const std::string& s) {
  return s | view::filter(isalnum);
}

void popular_words() {
  const auto words = istream_range<std::string>(std::cin)
      | view::transform(string_to_lower)
      | view::transform(string_only_alnum)
      | view::remove_if(&std::string::empty)
      | to_vector | action::sort;

  const auto results = words
      | view::group_by(std::equal_to<>())
      | view::transform([](const auto& group) {
          const auto begin = std::begin(group);
          const auto end = std::end(group);
          // Not to use std::distance
          const size_t size = distance(begin, end);
          const auto word = *begin;
          return std::make_pair(size, word);
        })
      | to_vector | action::sort;
}

template <typename C, typename P>
auto filter_by_index(C col, P index_filter_pred) {
  return view::zip(view::ints(0), col)
      | view::filter([&](auto p) {
          return index_filter_pred(p.first);
        })
      | view::transform([] (auto p) {
          return p.second;
        });
}

int main(int argc, char const *argv[]) {

}
