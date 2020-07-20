#include "SystemNode.h"

/*#include "WireNode.h"
#include "PinNode.h"*/

SystemNode::SystemNode(QString value, Node *parent):Node()
{
//    displayName =  element.attribute("displayName");
//    comment     =  element.attribute("comment");
//    isDisplay   =  ((element.attribute("isDisplay")).toInt());
    idName      =  value;
    displayName = value;


    if(idName == "")
        idName = displayName;
    pathName = idName;

    parent->addChild(this);
    addParent(parent);
}
SystemNode::SystemNode():Node()
{

}
Node *SystemNode::clone()
{
    SystemNode *rootNode = new SystemNode;

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
