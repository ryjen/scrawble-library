#ifndef SCRAWBLE_NODE_H
#define SCRAWBLE_NODE_H

#include <map>
#include <memory>

namespace scrawble
{
    class Node : public std::enable_shared_from_this<Node>
    {
       public:
        typedef char Type;
        typedef std::shared_ptr<Node> Ptr;
        constexpr static const char CROSS_ANCHOR_CHAR = '#';

        Node();
        Node(const Type &value, bool terminal, const Ptr &parentNode);

        Node &setRoot(bool value);
        bool isRoot() const;

        bool isCrossAnchorNode() const;

        Node &setLetter(const Type &value);
        Type getLetter() const;

        Node &setTerminal(bool value);
        bool isTerminal() const;

        Node &setParentNode(const Ptr &value);
        Ptr getParentNode() const;

        Ptr addChildNode(const Type &value, bool terminal);
        Ptr getOrAddChildNode(const Type &value, bool terminal);

        Ptr addChildCrossAnchorNode();

        Ptr getChildNode(const Type &value) const;
        Ptr getCrossAnchorNode() const;

        std::vector<Ptr> getChildNodes() const;

       private:
        bool root_;
        Type letter_;
        bool terminal_;
        Ptr parentNode_;
        std::map<Type, Ptr> childNodes_;
    };
}  // namespace scrawble

#endif
