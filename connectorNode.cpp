#include "connectorNode.h"
#include "./globalFunc/gl_func.h"

ConnectorNode::ConnectorNode(QString id,
                             QString typeConBlock,
                             QString typeConWire,
                             Node *parent):Node()
{
    idName        = id;
    typeConnectorBlock.clear();
    typeConnectorWire.clear();
    connectWith = nullptr;
    if(typeConBlock != "-")
        typeConnectorBlock = typeConBlock;
    if(typeConWire != "-")
        typeConnectorWire = typeConWire;
    pathName    = idName;
    listForCompleter<<displayName;

    parent->addChild(this);
    addParent(parent);
}
ConnectorNode::ConnectorNode():Node()
{
    connectWith = nullptr;

}
Node *ConnectorNode::clone()
{
    ConnectorNode *rootNode = new ConnectorNode;

    rootNode->idName        = this->idName;
    rootNode->displayName   = this->displayName;
    rootNode->comment       = this->comment;
    rootNode->pathName      = this->pathName;

    rootNode->typeConnectorBlock = this->typeConnectorBlock;
    rootNode->typeConnectorWire = this->typeConnectorWire;

    for(auto i:child)
    {
        Node* new_node = i->clone();
        rootNode->addChild(new_node);
    }
    return rootNode;
}
ConnectorNode::~ConnectorNode() {
        // TODO Auto-generated destructor stub
}
