#include <scrawble/config.h>

namespace scrawble
{
    Config::Config()
    {
    }

    const std::vector<Config::Tile> &Config::tile_distributions() const
    {
        return letters_;
    }

    const std::string &Config::dictionary_file_name() const
    {
        return dictionary_;
    }
}
