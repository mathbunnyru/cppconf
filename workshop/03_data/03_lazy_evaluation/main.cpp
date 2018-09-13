
#include <functional>
#include <string>
#include <iostream>
#include <mutex>
#include <optional>
// alternatively #include <boost/optional/optional.hpp>

template <typename F>
class lazy_val {
private:
    F m_function;

    mutable std::optional<decltype(m_function())> m_value;
    mutable std::mutex m_value_lock;

public:
    lazy_val(F function)
        : m_function(function)
    {
    }

    lazy_val(lazy_val &&other)
        : m_function(std::move(other.m_function))
    {
    }

    operator decltype(m_function()) () const
    {
        std::lock_guard<std::mutex> lock(m_value_lock);

        if (!m_value) {
            m_value = std::invoke(m_function);
        }

        return *m_value;
    }

};

// Template argument type deduction does not work for classes (til C++17),
// so we need to create the make_ function which will trigger the template
// argument type deduction (similar to std::pair and std::make_pair)
template <typename F>
lazy_val<F> make_lazy_val(F &&function)
{
    return lazy_val<F>(std::forward<F>(function));
}


// Alternative to make_ function is to define a pretty macro
// which will allow us to 'invent' a new C++ keyword for defining lazy
// values
struct _make_lazy_val_helper {
    template <typename F>
    auto operator - (F &&function) const
    {
        return lazy_val<F>(function);
    }
} make_lazy_val_helper;

#define lazy make_lazy_val_helper - [&]


int main(int argc, char *argv[])
{
    int number = 6;

    auto val = lazy {
        std::cout << "Calculating the answer..." << std::endl;
        std::cout << "while the number is: " << number << std::endl;
        return 42;
    };

    number = 2;

    std::cout << "Lazy value defined, lets evaluate it:" << std::endl;

    std::cout << val << std::endl;

    // In C++17, things are easier - no need for make_ or for macros.
    // This also allows us to choose how we capture variables from
    // the surrounding scope
    lazy_val val2 = [] {
        std::cout << "Calculating the answer..." << std::endl;
        return 42;
    };

    std::cout << "Lazy value defined, lets evaluate it several times:" << std::endl;

    std::cout << val2 << val2 << val2 << std::endl;
}

