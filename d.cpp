#include <optional>
#include <cmath>
#include <vector>
#include <string>
#include <future>

std::optional<double> sq_root(double d) {
  if (d >= 0.) {
    return {std::sqrt(d)};
  } else {
    return std::nullopt;
  }
}

template <typename T, typename Trafo>
auto transform(
    const std::optional<T>& opt,
    Trafo trafo) {
  if (opt) {
    return std::make_optional(trafo(*opt));
  } else {
    return {};
  }
}

template <typename Trafo>
struct trafo_helper {
  Trafo trafo;
};

template <typename Trafo>
auto transform(Trafo trafo) {
  return trafo_helper<Trafo>(trafo);
}

template<typename T, typename Trafo>
auto operator| (const std::optional<T>& opt, trafo_helper<Trafo> t) {

}

int main(int argc, char const *argv[]) {
  std::optional<std::string> username;
  username
      | transform(fetch_user_full_name)
      | transform(generate_md)
      | transform(md_2_html);

  std::vector<std::string> usernames;

  usernames
      | transform(fetch_user_full_name)
      | transform(generate_md)
      | transform(md_2_html);

  std::future<std::string> username_in_the_future;

  return 0;
}
