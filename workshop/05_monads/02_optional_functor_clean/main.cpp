#include <iostream>
#include <optional>
#include <string>
#include <vector>


template <typename T1, typename Trafo>
auto transform(const std::optional<T1>& opt, Trafo f)
    -> decltype(std::make_optional(f(opt.value())))
{
    if (opt) {
        return std::make_optional(f(opt.value()));
    } else {
        return {};
    }
}


template <typename Trafo>
struct transform_def {
    transform_def(Trafo trafo)
        : trafo(trafo)
    {
    }

    Trafo trafo;
};


template <typename Trafo>
auto transform(Trafo&& trafo)
{
    return transform_def<Trafo>(std::forward<Trafo>(trafo));
}

template <typename OptType, typename TrafoType>
auto operator| (const std::optional<OptType>& opt,
                const transform_def<TrafoType>& trafo_def)
{
    return transform(opt, trafo_def.trafo);
}


struct to_string_function_object {
    template <typename T>
    std::string operator() (T&& t) const
    {
        return std::to_string(std::forward<T>(t));
    }

    std::string operator() (bool t) const
    {
        return t ? "true" : "false";
    }
};

inline to_string_function_object to_string;

template <typename Out>
struct cast_to_function_object {
    template <typename In>
    Out operator() (In &&in) const
    {
        return static_cast<Out>(std::forward<In>(in));
    }
};

template <typename Out>
inline cast_to_function_object<Out> cast_to;



int main(int argc, char* argv[])
{
    auto i = std::make_optional('.');

    auto result = i | transform(isalnum)
                    | transform(cast_to<bool>)
                    | transform(to_string);

    if (result) {
        std::cout << *result << std::endl;
    }

    return 0;
}
