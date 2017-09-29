#include <scrawble/core/gaddag.h>
#include <algorithm>
#include <string>
#include <vector>

namespace scrawble
{
    namespace algorithm
    {
        void search(const std::string &);
    }

    namespace helper
    {
        std::string get_word(const std::string &str)
        {
            std::string word;

            auto br = str.find(Node::Break);

            for (int i = br - 1; i >= 0; i--)
                word += str[i];

            for (int i = br + 1; i < str.size(); i++)
                word += str[i];

            return word;
        }

        void containsHookWithRackRecursive(const Node::Ptr &node, std::set<std::string> &rtn, std::string &letters,
                                           std::string &rack, const std::string &hook)
        {
            // Null nodes represent the EOW, so return the word.
            if (node == nullptr || *node == Node::Eow) {
                auto w = get_word(letters);
                if (rtn.find(w) != rtn.end())
                    rtn.insert(w);
                return;
            }

            // If the hook still contains letters, process those first.
            if (!hook.empty()) {
                letters += (node->letter() != Node::Root ? std::to_string(node->letter()) : "");

                if (node->contains(hook[0])) {
                    auto h = hook.substr(0, 1);  // Pop the letter off the hook
                    containsHookWithRackRecursive(node->child(hook[0]), rtn, letters, rack, h);
                }
            } else {
                letters += node->letter() != Node::Root ? std::to_string(node->letter()) : "";

                node->visit([&rack, &rtn, &letters, &hook](const Node::Type &type, const Node::Ptr &node) {
                    if (rack.find(type) != std::string::npos || type == Node::Eow || type == Node::Break) {
                        if (node->letter() != Node::Eow && node->letter() != Node::Break) {
                            auto it = rack.find(node->letter());
                            if (it != std::string::npos) {
                                rack.erase(it);
                            }
                        }
                        containsHookWithRackRecursive(node->child(node->letter()), rtn, letters, rack, hook);
                    }
                });
            }
        }
    }

    Gaddag::Gaddag() : root_(std::make_shared<Node>())
    {
    }

    Gaddag &Gaddag::add(const std::string &word)
    {
        std::vector<Node::Ptr> prevNodes;
        for (int i = 1; i <= word.length(); i++) {
            auto prefix = word.substr(0, i);
            auto coded = std::string(prefix.rbegin(), prefix.rend());
            coded += Node::Break;
            coded += word.substr(i, word.length() - i);
            coded += Node::Eow;

            auto currentNode = root_;
            auto breakFound = false;
            auto j = 0;
            for (auto ch : word) {
                if (breakFound && prevNodes.size() > j) {
                    currentNode->add_child(ch, prevNodes[j]);
                    break;
                }

                currentNode = currentNode->add_child(ch);

                if (prevNodes.size() == j) {
                    prevNodes.push_back(currentNode);
                }

                if (ch == Node::Break) {
                    breakFound = true;
                }

                j++;
            }
        }
        return *this;
    }

    std::set<std::string> Gaddag::find(const std::string &hook, const std::string &rack) const
    {
        auto rev = std::string(hook.rbegin(), hook.rend());

        std::transform(rev.begin(), rev.end(), rev.begin(), ::tolower);

        std::set<std::string> set;
        std::string letters;
        std::string tempRack(rack);

        helper::containsHookWithRackRecursive(root_, set, letters, tempRack, rev);

        return set;
    }
}