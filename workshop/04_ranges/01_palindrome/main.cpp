#include <iostream>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/algorithm/equal.hpp>

using namespace ranges::v3;

bool is_same_letter(char left, char right)
{
    return std::tolower(left) == std::tolower(right);
}

bool is_palindrome(const std::string & str)
{
    return ranges::equal(str, view::reverse(str), is_same_letter);

    // or using the pipe syntax
    // return ranges::equal(str, str | view::reverse, is_same_letter);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " word" << std::endl;
        return 1;
    }

    std::cout << argv[1] <<
        (is_palindrome(std::string(argv[1])) ? " is ":" is not ")
        << "a palindrome"
        << std::endl;

    return 0;
}
