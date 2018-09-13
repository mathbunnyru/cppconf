
#include <functional>
#include <string>
#include <iostream>

#include "person.h"
#include "pet.h"
#include "vehicle.h"


// C -- functions and function pointers (and function references)
std::string fn_name(const person &value)
{
    return value.name();
}


// C++ -- function templates
template <typename T>
std::string tp_name(T &&value)
{
    return std::forward<T>(value).name();
}


// C++ -- classes with the call operator
class cs_name {
public:
    cs_name(std::string quote)
        : m_quote(quote)
    {
    }

    std::string operator() (const person &value) const
    {
        return value.name() + ": " + m_quote;
    }

private:
    std::string m_quote;

};


// C++ -- generic classes with a call operator
template <typename Type = void>
class csgen_name {
public:
    csgen_name(std::string quote)
        : m_quote(quote)
    {
    }

    std::string operator() (const Type &value) const
    {
        return value.name() + ": " + m_quote;
    }

private:
    std::string m_quote;

};


// C++ -- generic call operator
class csgen2_name {
public:
    csgen2_name(std::string quote)
        : m_quote(quote)
    {
    }

    template <typename Type>
    std::string operator() (const Type &value) const
    {
        return value.name() + ": " + m_quote;
    }

private:
    std::string m_quote;

};


// C++ -- void specialization
template <>
class csgen_name<void> {
public:
    csgen_name(std::string quote)
        : m_quote(quote)
    {
    }

    template <typename Type>
    std::string operator() (const Type &value) const
    {
        return value.name() + ": " + m_quote;
    }

private:
    std::string m_quote;

};


// Function objects:
//  - functions and function pointers
//  - values castable to a function pointer (avoid this)
//  - objects with a call operator
//  - objects with a generic call operator
//  - lambdas as syntactic sugar for the above

template < typename Type
         , typename DType = typename std::decay<Type>::type
         >
std::string name(Type &&value)
{
    return std::invoke(
            &DType::name,
            std::forward<Type>(value)
        );
}


int main(int argc, char *argv[])
{
    person  brigadier("Jack", "Ripper");
    pet     dog("Gaspode");

    vehicle car{"Ford T"};

    csgen_name<> f("POE");

    std::cout
        << f(brigadier) << std::endl
        << f(dog)       << std::endl
        ;

    // C++17
    // What about member varaibles and member functions?
    std::cout
        << std::invoke(&pet::name, dog)     << std::endl
        << std::invoke(&vehicle::name, car) << std::endl
        << std::invoke(
                &decltype(dog)::name, dog)  << std::endl

        << name(dog)                        << std::endl
        << name(brigadier)                  << std::endl
        << name(car)                        << std::endl
        ;

    return 0;
}

