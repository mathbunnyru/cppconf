
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <functional>


// An item is selected if the first char is a star
bool is_selected(const std::string &item)
{
    return item[0] == '*';
}

template <typename It, typename Pred>
void move_selection(It first, It last, It destination, Pred predicate)
{
    std::stable_partition(first, destination,
                          std::not_fn(predicate));
    std::stable_partition(destination, last,
                          predicate);
}


int main(int argc, char *argv[])
{
    std::vector<std::string> items {
            "aardvark",
            "compunctious",
            "**congratulations**",
            "contrafribblarity",
            "contrary",
            "dictionary",
            "**interphrastical**",
            "**patronise**",
            "**pericombobulation**",
            "phrasmotic",
            "**syllables**"
        };

    move_selection(
            std::begin(items), std::end(items), std::begin(items) + 5,
            is_selected
        );

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}
