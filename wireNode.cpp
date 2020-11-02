
#include "wireNode.h"
#include "./globalFunc/gl_func.h"
#include <QDebug>
WireNode::WireNode(QString id,
                   QString type,
                  // QString idNameCoord_,
                   Node *parent):Node()
{
//    displayName = element.attribute("displayName","None");
    idName      = id;
    length = 0;

   //
//    if(idNameCoord_.isEmpty() == false)
//    {
//        idNameCoord = idNameCoord_;
//        qDebug()<<idNameCoord<<"\n";
//    }
    typeWire.clear();
    if(type != "-")
        typeWire =  type;
    toPin       = nullptr;
    fullConnected = false;
//    pathName    = idName;

//    comment     = element.attribute("comment");
//    isDisplay   = ((element.attribute("isDisplay")).toInt());

    pathName = idName;
    listForCompleter<<displayName;

    parent->addChild(this);
    addParent(parent);
}
WireNode::WireNode():Node()
{
    toPin       = nullptr;
    fullConnected = false;
    length = 0;

}

Node *WireNode::clone()
{
    WireNode *rootNode = new WireNode;

    //rootNode->idNameCoord   = this->idNameCoord;
    rootNode->idName        = this->idName;
    rootNode->displayName   = this->displayName;
    rootNode->comment       = this->comment;
    rootNode->pathName      = this->pathName;

    rootNode->fullConnected = false;//this->fullConnected;

    rootNode->typeWire    = this->typeWire;
    for(auto i:child)
    {
        Node* new_node = i->clone();
        rootNode->addChild(new_node);
    }
    return rootNode;
}
