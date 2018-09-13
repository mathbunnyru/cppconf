
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>


bool is_selected(const std::string &item)
{
    return item[0] == '*';
}

auto is_selected_tt(const std::string &item) -> bool
{
    return item[0] == '*';
}

auto is_selected_at(const std::string &item)
{
    return item[0] == '*';
}

auto is_selected_at(const auto &item)
{
    return false;
}

// auto error_at(bool flag)
// {
//     return flag ? 42
//                 : std::string("42");
// }

template <typename T>
struct err;

int main(int argc, char *argv[])
{
    // err<decltype(is_selected_at(""))> e;
    // err<decltype(is_selected_at(42))> e;
}

