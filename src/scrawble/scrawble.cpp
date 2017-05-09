#include <scrawble/lexicon/node.h>
#include <scrawble/scrawble.h>
#include <scrawble/vt100.h>
#include <cassert>
#include <fstream>

void scrawble::load(const std::string& filePath)
{
    load(config(filePath));
}

void scrawble::load(const config& conf)
{
    std::ifstream in(conf.dictionary());

    assert(in.is_open());

    for (std::string line; std::getline(in, line);) {
        dictionary_.push(line);
    }

    bag_.init(conf);

    player plr;

    players_[this_player_index] = plr;

    for (int i = 0; i < player::rack_size; i++) {
        plr.push(bag_.next());
    }
}
scrawble::scrawble() : turn_(0), players_(max_players), state_(Running)
{
}

void scrawble::update()
{
    term_.update(*this);
}

void scrawble::render()
{
    term_.render(*this);
}

player& scrawble::get_player()
{
    return players_[this_player_index];
}

board& scrawble::get_board()
{
    return board_;
}

void scrawble::finish_turn()
{
    if (++turn_ > players_.size()) {
        turn_ = 0;
    }
}

void scrawble::quit()
{
    state_ = Stopped;
}

bool scrawble::is_over() const
{
    return state_ == Stopped;
}

void scrawble::search(int x, int y, const std::vector<tile>& rack, const std::set<lexicon::move>& pool) const
{
    node root;
}
