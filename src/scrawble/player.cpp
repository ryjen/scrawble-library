#include <scrawble/game_logic.h>
#include <scrawble/player.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

namespace scrawble
{
    player::player() : rack_(), score_(0), name_()
    {
    }

    const scrawble::rack& player::rack() const
    {
        return rack_;
    }

    scrawble::rack& player::rack()
    {
        return rack_;
    }

    player& player::add_score(int score)
    {
        score_ += score;
        return *this;
    }

    const std::string& player::name() const
    {
        return name_;
    }

    const int player::score() const
    {
        return score_;
    }
}
