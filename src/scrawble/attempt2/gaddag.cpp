#include <scrawble/gaddag.h>
#include <scrawble/path.h>
#include <scrawble/word.h>

namespace scrawble
{
    gaddag::gaddag() : root_(std::make_shared<node>())
    {
    }

    gaddag::gaddag(const gaddag &other) : root_(other.root_)
    {
    }

    gaddag::gaddag(gaddag &&other) : root_(std::move(other.root_))
    {
        other.root_ = nullptr;
    }

    gaddag::~gaddag()
    {
    }

    gaddag &gaddag::operator=(const gaddag &other)
    {
        root_ = other.root_;
        return *this;
    }
    gaddag &gaddag::operator=(gaddag &&other)
    {
        root_ = std::move(other.root_);
        other.root_ = nullptr;
        return *this;
    }

    gaddag &gaddag::push(const std::string &value)
    {
        value_list reversed(value.rbegin(), value.rend());
        reversed.push_back(path::DELIMITER);
        root_->create_final_path(reversed);

        scrawble::word word(value);

        for (auto &path : word.delimited_paths()) {
            root_->create_final_path(path.to_array());
        }

        return *this;
    }

    std::set<std::string> gaddag::find(const std::string &substr) const
    {
        // chop the first two into a seperate vector
        if (substr.length() < 2) {
            return {};
        }

        value_list params(substr.begin(), substr.begin() + 2);

        value_list last_values(substr.begin() + 2, substr.end());

        value_list reversed(last_values.rbegin(), last_values.rend());

        if (!root_->is_path(reversed)) {
            return {};
        }

        std::set<std::string> result;

        auto paths = root_->follow_path(reversed);

        for (auto &final : paths->final_paths()) {
            if (!final->starts_with(params)) {
                continue;
            }

            scrawble::path path(reversed, final);

            result.insert(path.to_word().to_string());
        }

        return result;
    }
}
