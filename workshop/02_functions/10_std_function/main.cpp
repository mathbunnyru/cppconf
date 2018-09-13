
#include <functional>
#include <string>
#include <iostream>

#include "person.h"
#include "pet.h"
#include "vehicle.h"


std::string fn_name(const person &value)
{
    return value.name();
}


template <typename T>
std::string tp_name(T &&value)
{
    return std::forward<T>(value).name();
}


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



int main(int argc, char *argv[])
{
    person brigadier("Jack", "Ripper");

    // We should always get functions as template arguments or with auto.
    // If this is not possible, std::function can be used. The cases for
    // this are:
    //  - we need a function to be a member variable in an ordinary class
    //  - we need to transport a function over different compilation units
    //
    // std::function can hold any callable, but it is not free

    std::function<std::string(person)> fn = fn_name;

    fn = tp_name<person>;

    fn = cs_name("POE");

    fn = csgen_name<>("POE");

    std::cout
        << fn(brigadier)
        << std::endl
        ;

    return 0;
}

