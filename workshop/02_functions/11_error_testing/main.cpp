
#include <functional>
#include <string>
#include <iostream>
#include <mutex>
#include <type_traits>

// Detection whether there is .error in a type

template <typename, typename = void>
struct has_error_member
    : public std::false_type {};

template<class T>
struct has_error_member<
        T, std::void_t<decltype(std::declval<T>().error)>>
    : public std::true_type {};

template<class T>
struct has_error_member<
        T, std::void_t<decltype(std::declval<T>().error())>>
    : public std::true_type {};


template <typename Type,
          typename HasError = typename has_error_member<Type>::type,
          typename DType = std::decay_t<Type>>
bool error(Type &&value)
{
    if constexpr (HasError()) {
        return std::invoke(&DType::error, std::forward<Type>(value));
    } else {
        std::cerr << "Warning: calling error_helper for types that do not have .error\n";
        return false;
    }
}


struct error_struct {
    int error;
};


class error_class {
public:
    error_class(bool err)
        : m_error(err)
    {
    }

    bool error() const
    {
        return m_error;
    }

private:
    bool m_error;
};


static_assert(has_error_member<error_struct>::value, "error_struct has .error");
static_assert(has_error_member<error_class>::value, "error_class has .error");
static_assert(!has_error_member<int>::value, "int does not have .error");


int main(int argc, char *argv[])
{
    int value = 2;
    error_struct e1{false};
    error_class e2{true};

    std::cout << error(value) << std::endl;
    std::cout << error(e1) << std::endl;
    std::cout << error(e2) << std::endl;
}

