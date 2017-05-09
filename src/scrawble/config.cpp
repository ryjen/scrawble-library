#include <scrawble/config.h>

using json = nlohmann::json;

config::config()
{
}

config::config(const std::string &filePath)
{
    load(filePath);
}

void config::load(const std::string &filepath)
{
    file_reader input(filepath);

    json j = input.to_json();

    dictionary_ = j["dictionary"];

    auto tiles = j["tiles"];

    for (auto tile : tiles) {
        int score = tile["score"];

        auto distributions = tile["letter_distributions"];

        for (auto it = distributions.begin(); it != distributions.end(); ++it) {
            letters_.emplace_back(score, it.value(), it.key());
        }
    }
}

const std::vector<config::tile> &config::letters() const
{
    return letters_;
}

const std::string &config::dictionary() const
{
    return dictionary_;
}

void config::load()
{
    load(DEFAULT_CONFIG_FILE);
}
file_reader::file_reader(const std::string &filePath) : input_(filePath)
{
    assert(input_.is_open());
}

file_reader::~file_reader()
{
    input_.close();
}

json file_reader::to_json()
{
    json j;
    // save current state
    auto state = input_.rdstate();
    auto pos = input_.tellg();

    // reset
    input_.clear();
    input_.seekg(0);

    // convert
    input_ >> j;

    // restore current state
    input_.clear(state);
    input_.seekg(pos);

    return j;
}

std::istream &operator>>(std::istream &is, file_reader::line &line)
{
    return std::getline(is, line);
}

file_reader::iterator file_reader::begin()
{
    return iterator(input_);
}
file_reader::iterator file_reader::end()
{
    return iterator();
}
