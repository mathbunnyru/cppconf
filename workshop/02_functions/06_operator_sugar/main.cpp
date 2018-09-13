
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

namespace detail {
    struct selection_tester_impl {
        selection_tester_impl(bool flag)
            : m_flag(flag)
        {
        }

        bool operator() (const std::string &item) const
        {
            return m_flag == (item[0] == '*');
        }

        selection_tester_impl operator==(bool flag) const
        {
            return selection_tester_impl(
                       flag ? m_flag : !m_flag
                    );
        }

        bool m_flag;
    };

}

detail::selection_tester_impl selected(true);
detail::selection_tester_impl not_selected(false);

template <typename Collection, typename Predicate>
void output_if(const Collection &c, Predicate p)
{
    std::copy_if(std::begin(c), std::end(c),
            std::ostream_iterator<std::string>(std::cout, "\n"),
            p);
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

    std::cout << "\nSelected:\n";
    output_if(items, selected);

    std::cout << "\nNot selected:\n";
    output_if(items, not_selected);

    std::cout << "\nSelected == true\n";
    output_if(items, selected == true);

    std::cout << "\nSelected == false\n";
    output_if(items, selected == false);

    std::cout << "\nNot selected == false\n";
    output_if(items, not_selected == false);

    return 0;
}

