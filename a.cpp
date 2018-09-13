#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <string>
#include <utility>
#include <ctype.h>

double average(const std::vector<int>& xs) {
  double sum = std::accumulate(
    std::begin(xs),
    std::end(xs),
    1.0,
    [] (auto acc, auto x) {
      return acc * x;
    }
  );
  return sum / xs.size();
}

bool is_same_letter(char left, char right) {
  return std::tolower(left) == std::tolower(right);
}

template<typename T>
bool is_palindrome(const T& xs) {
  return std::equal(
    xs.cbegin(), xs.cend(),
    xs.crbegin(),
    is_same_letter
  );
}

bool is_selected(const std::string& s) {
  return s[0] == '*';
}

std::vector<bool> find_selected() {
  std::vector<std::string> items {
    "aasdasdfsfd",
    "afasgsdfg",
    "25ben",
    "***adfsdfgsgf",
    "**fsdf",
    "tret"
  };

  std::vector<bool> selected_markers(items.size());
  std::transform(
    std::cbegin(items),
    std::cend(items),
    std::begin(selected_markers),
    is_selected
  );
  return selected_markers;
}

// accumulate takes init

// Recursive tail optimization
// int sum(acc, {}) = acc
// int sum(acc, xs) = sum(acc + head(xs), tail(xs))

// What can change:
// initial acc value
// xs
// function

// fold(xs, acc, f) - actually, std::transform

template<typename ItBegin, typename ItEnd,
         typename Init, typename Func>
Init cxx20accumulate(ItBegin begin, ItEnd end, Init acc, Func func) {
  for (; begin != end; ++ begin) {
    acc = func(acc, *begin);
  }

  return acc;
}

std::string find_even_string(const std::vector<int>& xs) {
  return std::accumulate(
    std::begin(xs),
    std::end(xs),
    std::string(),
    [] (const std::string& s, int i) {
      return i % 2 == 0
        ? s + std::to_string(i)
        : s;
    }
  );
}

// TODO(asalikhov) : implement filter, transform using accumulate

std::vector<std::string> split(const std::string& s) {
  std::vector<std::string> result;

  auto i = s.cbegin();

  while (i != s.cend()) {
    i = std::find_if_not(i, s.cend(), isspace);

    auto j = std::find_if(i, s.cend(), isspace);

    if (i != j) {
      result.emplace_back(i, j);
    }
  }
  return result;
}

template<typename It>
std::pair<It, It> slide_selection(
    It selection_begin,
    It selection_end,
    It destination) {
  if (destination < selection_begin) {
    return {
      destination,
      std::rotate(destination, selection_begin, selection_end)
    };
  }

  if (destination > selection_end) {
    return {
      std::rotate(selection_begin, selection_end, destination),
      destination
    };
  }
  return {selection_begin, selection_end};
}

void divide_by_modulo() {
  std::vector<int> xs = { 1, 2, 3, 4, 5, 6, 7 };
  auto first = std::stable_partition(
    std::begin(xs), std::end(xs),
    [] (int i) { return i % 3 == 0; }
  );

  std::stable_partition(
    first, std::end(xs),
    [] (int i) { return i % 3 == 1; }
  );
}

template<typename It, typename Pred>
std::pair<It, It> move_selection(It begin, It end, It dest, Pred pred) {
  return {
    std::stable_partition(
      begin, dest, std::not_fn(pred)
    ),
    std::stable_partition(
      dest, end, pred
    )
  };
}

template<typename T>
int count_adj_equals(const T& xs) {
  return std::inner_product(
    std::begin(xs), std::end(xs) - 1,
    std::begin(xs) + 1,
    0,
    std::plus<>(),
    std::equal_to<>()
  );
}

int main(int argc, char const *argv[]) {


}