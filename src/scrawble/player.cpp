#include <scrawble/game_logic.h>
#include <scrawble/player.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

namespace scrawble
{
    Player::Player() : rack_(), score_(0), name_()
    {
    }

    const Rack& Player::rack() const
    {
        return rack_;
    }

    Rack& Player::rack()
    {
        return rack_;
    }

    Player& Player::add_score(int score)
    {
        score_ += score;
        return *this;
    }

    const std::string& Player::name() const
    {
        return name_;
    }

    const int Player::score() const
    {
        return score_;
    }
}
