
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>


bool is_selected(const std::string &item)
{
    return item[0] == '*';
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

    // remove_if just moves the values that should not be deleted
    // to the front of the collection
    items.erase(
            std::remove_if(std::begin(items), std::end(items),
                           [] (const auto &item) { return !is_selected(item); }),
            std::end(items)
        );

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    // alternative to erase-remove would be std::copy_if

    return 0;
}
