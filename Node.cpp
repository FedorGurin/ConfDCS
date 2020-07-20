
#include "Node.h"

quint64 Node::countId = 0;
Node::Node(QString name)
{
    child.clear();
    parent      = nullptr;
    pathName    = "";
    displayName = "";
    idName      = name;
    left        = nullptr;
    right       = nullptr;
    isDisplay   = true;
    Node::countId++;
    Node::id = countId;
}
Node* Node::clone()
{
    Node *rootNode = new Node;

    rootNode->idName        = this->idName;
    rootNode->displayName   = this->displayName;
    rootNode->comment       = this->comment;
    rootNode->pathName      = this->pathName;

    for(auto i:child)
    {
        Node* new_node = i->clone();
        rootNode->addChild(new_node);
    }
    return rootNode;
}
Node::~Node()
{
    // TODO Auto-generated destructor stub
}
