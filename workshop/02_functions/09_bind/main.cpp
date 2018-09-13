
#include <functional>
#include <string>
#include <iostream>

#include "person.h"

enum person_format {
    first_name,
    last_name,
    full_name
};

std::ostream &print_person(person_format format, const person &person)
{
    return
        format == first_name ?
            (std::cout << person.name()) :
        format == last_name ?
            (std::cout << person.surname()) :
        // otherwise
            (std::cout << person.name() << " " << person.surname());
}



int main(int argc, char *argv[])
{
    using namespace std::placeholders;

    person brigadier("Jack", "Ripper");

    print_person(last_name, brigadier)
        << std::endl;



    // We are binding a single argument, while the other one will
    // be specified when the function object is called

    auto print_first_name = std::bind(print_person, first_name, _1);
    auto print_last_name = std::bind(print_person, last_name, _1);

    print_first_name(brigadier)
        << std::endl;
    print_last_name(brigadier)
        << std::endl;



    // Swapping the order of arguments of a function

    auto flip_print_person = std::bind(print_person, _2, _1);

    flip_print_person(brigadier, full_name)
        << std::endl;



    // Binding both arguments to simulate lazy evaluation

    auto lazy_print_person = std::bind(print_person, full_name, brigadier);

    lazy_print_person()
        << std::endl;

    return 0;
}

