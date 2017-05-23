#include <scrawble/config.h>

namespace scrawble
{
    config::config()
    {
    }

    const std::vector<config::tile> &config::letters() const
    {
        return letters_;
    }

    const std::string &config::dictionary() const
    {
        return dictionary_;
    }
}
