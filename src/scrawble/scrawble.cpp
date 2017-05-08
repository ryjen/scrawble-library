#include <scrawble/lexicon/node.h>
#include <scrawble/scrawble.h>
#include <cassert>
#include <fstream>

std::ostream &operator<<(std::ostream &out, const scrawble &scrawble)
{
    scrawble.print(out);
    return out;
}

scrawble::scrawble()
{
    std::ifstream in(DICTIONARY_FILE);

    assert(in.is_open());

    for (std::string line; std::getline(in, line);) {
        dictionary_.push(line);
    }
}


void scrawble::print(std::ostream &out) const
{
    board_.print(out);
}

void scrawble::search(int x, int y, const std::vector<char> &rack, const std::set<move> &pool) const
{
    node root;
}