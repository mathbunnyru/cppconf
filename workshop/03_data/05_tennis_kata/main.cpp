#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <variant>

// A helper to create overloaded function objects
template <typename... Fs>
struct overloaded : Fs... { using Fs::operator()...; };

template <typename... Fs> overloaded(Fs...) -> overloaded<Fs...>;

class tennis_game {
    enum class points {
        love,
        fifteen,
        thirty
    };

    enum class player {
        player_1,
        player_2
    };

    struct normal_scoring {
        points player_1_score;
        points player_2_score;
    };

    struct forty_scoring {
        player lead;
        points other_score;
    };

    struct deuce {};

    struct advantage {
        player lead;
    };

    std::variant<normal_scoring,
                 forty_scoring,
                 deuce,
                 advantage> m_state;

    void point_for(player p)
    {
        // :::
    }
};
