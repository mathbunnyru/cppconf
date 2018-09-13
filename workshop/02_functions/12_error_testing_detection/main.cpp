
#include <functional>
#include <string>
#include <iostream>
#include <mutex>
#include <type_traits>
#include <experimental/type_traits>

// Detection whether there is .error in a type

template <typename T>
using has_error_member_variable = decltype(std::declval<T>().error);

template <typename T>
using has_error_member_function = decltype(std::declval<T>().error());

template <typename Type,
          typename DType = std::decay_t<Type>>
bool error(Type &&value)
{
    if constexpr (
            std::experimental::is_detected_v<has_error_member_variable, Type> ||
            std::experimental::is_detected_v<has_error_member_function, Type>
            ) {
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


static_assert(std::experimental::is_detected_v<has_error_member_variable, error_struct>, "error_struct has .error");
static_assert(not std::experimental::is_detected_v<has_error_member_variable, error_class>, "error_class has .error");
static_assert(not std::experimental::is_detected_v<has_error_member_variable, int>, "int does not have .error");

static_assert(not std::experimental::is_detected_v<has_error_member_function, error_struct>, "error_struct has .error");
static_assert(std::experimental::is_detected_v<has_error_member_function, error_class>, "error_class has .error");
static_assert(not std::experimental::is_detected_v<has_error_member_function, int>, "int does not have .error");


int main(int argc, char *argv[])
{
    int value = 2;
    error_struct e1{false};
    error_class e2{true};

    std::cout << error(value) << std::endl;
    std::cout << error(e1) << std::endl;
    std::cout << error(e2) << std::endl;
}

