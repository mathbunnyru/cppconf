
#include <iostream>
#include <algorithm>
#include <string>

bool is_same_letter(char left, char right)
{
    return std::tolower(left) == std::tolower(right);
}

bool is_palindrome(const std::string & str)
{
    // Problem with std::equal: When comparing for equality in general,
    // we first need to check that both sequences contain the same number
    // of elements.
    // Here, this is not a problem since a reversed sequence has the same
    // number of elements as the original one.
    return std::equal(str.cbegin(), str.cend(), str.crbegin(), is_same_letter);
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " word" << std::endl;
        return 1;
    }

    std::cout << argv[1] <<
        (is_palindrome(argv[1]) ? " is ":" is not ")
        << "a palindrome"
        << std::endl;

    return 0;
}
