
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

std::vector<std::string> split(const std::string& str)
{
    std::vector<std::string> result;

    auto i = str.cbegin();

    // Going til we reach the end of the string
    while (i != str.cend()) {

        // Skip the spaces - returns the iterator to the start of the
        // next word, if any
        i = std::find_if_not(i, str.cend(), isspace);

        // Where is the end of the word?
        auto j = std::find_if(i, str.cend(), isspace);

        // Adding the word into the resulting vector
        if (i != str.cend()) {
            result.push_back(std::string(i, j));
        }

        // Search for the next word
        i = j;
    }

    return result;
}

int main(int argc, const char *argv[])
{
    const auto message = split("Splitting atoms or strings");

    std::copy(message.cbegin(), message.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}

