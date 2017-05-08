#include <scrawble/lexicon/node.h>
#include <scrawble/scrawble.h>
#include <scrawble/vt100.h>
#include <cassert>
#include <fstream>

std::ostream& operator<<(std::ostream& out, const scrawble& scrawble)
{
    scrawble.print(out);
    return out;
}

scrawble::scrawble(const config& conf) : bag_(conf)
{
    std::ifstream in(conf.dictionary());

    assert(in.is_open());

    for (std::string line; std::getline(in, line);) {
        dictionary_.push(line);
    }

    auto plr = std::make_shared<player>();

    players_[this_player] = plr;

    for (int i = 0; i < player::rack_size; i++) {
        plr->push(bag_.next());
    }
}

void scrawble::print(std::ostream& out) const
{
    board_.print(out);

    players_[this_player]->print(out);

    file_reader reader("assets/help.txt");

    out << vt100::cursor::save();

    int row = 2;
    for (auto line : reader) {
        out << vt100::cursor::set(row++, 80);
        out << line;
    }

    out << vt100::cursor::restore();
}

void scrawble::search(int x, int y, const std::vector<char>& rack, const std::set<move>& pool) const
{
    node root;
}