
#include <iostream>
#include <string>


bool is_selected(const std::string &item)
{
    return item[0] == '*';
}

int main(int argc, char *argv[])
{
    std::cout << is_selected("**Hello**") << std::endl;
    std::cout << (*is_selected)("**Hello**") << std::endl;

    std::cout <<
        (******************************
         */* Insane number of stars */*
         ******************************
         is_selected
        )("**Hello**") << std::endl;
}

