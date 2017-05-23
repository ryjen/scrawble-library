#include <scrawble/config.h>

namespace scrawble
{
    config::config()
    {
    }

    const std::vector<config::tile> &config::tile_distributions() const
    {
        return letters_;
    }

    const std::string &config::dictionary_file_name() const
    {
        return dictionary_;
    }
}
