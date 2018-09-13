#include <cassert>
#include <functional>
#include <experimental/optional>
#include <string>
#include <variant>

// - functions, function pointers
// - object with operator()
// - lambdas
// - object that can be cast to function ptrs

// std::multiplies<int>()
// std::multiplies<>()

template<typename T>
class fngen {
public:
  bool operator() () const { return true; }
};

class fnpropergen {
public:
  template<typename T>
  bool operator() (T something) const { return true; }
};

auto f() -> int {
  return 0;
}

int s = (******f)();

template <typename Pred>
void f(Pred pred) {
}

std::function<int()> m;


template <
  typename F,
  typename T = std::decay_t<decltype(
    std::declval<F>()()
  )>
>
class lazy_val {
public:
  lazy_val(F f) : m_fun(f) {}

  operator const T& () const {
    if (!m_cache) {
      m_cache = m_fun();
    }
    return *m_cache;
  }

private:
  std::experimental::optional<T> m_cache;
  F m_fun;
};

template<typename F>
auto make_lazy_val(F&& f) {
  return lazy_val<F>(std::forward<F>(f));
}

struct dummy {
  template<typename F>
  auto operator- (F&& f) const {
    return lazy_val<F>(std::forward<F>(f));
  }
};

#define lazy dummy() - [&]

auto lazy_func() {
  auto value = make_lazy_val([]() {
    return 42;
  });

  auto value2 = dummy() - [&] {
    return 42;
  };

  auto value3 = lazy {
    return 42;
  };

  // Most simple, c++17
  lazy_val v = []() {
    return 42;
  };
}

template <typename... Fs>
struct overloaded : Fs... {
  using Fs::operator()...;
};

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// overloaded {
//   [] (int x) {},
//   [] (std::string) {},
//   [] (auto x) {}
// }

class program_t {
public:
  void counting_finished() {
    const auto* state = std::get_if<running_t>(&m_state);
    assert(state);

    m_state = finished_t{state->count};
  }

  size_t count() const {
    return std::visit(
      [](const auto & d) {
        if constexpr (std::is_same_v<std::decay_t<decltype(d)>, init_t>) {
          return 0;
        } else {
          return d.count;
        }
      },
      m_state
    );

    // Or
    return std::visit(
      overloaded {
        [] (init_t) { return 0; },
        [] (const auto& s) { return s.count; }
      },
      m_state
    );
  }

private:
  class init_t {
    std::string url;
  };

  struct running_t {
    int count;
  };

  struct finished_t {
    int count;
  };

  std::variant<init_t, running_t, finished_t> m_state;
};

int main(int argc, char const *argv[]) {
  return 0;
}
