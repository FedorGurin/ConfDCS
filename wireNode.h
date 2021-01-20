#ifndef WIRENODE_H
#define WIRENODE_H
#include "node.h"
#include <stdint.h>
#include "pinNode.h"
//! класс объединения одинаковых полей
class WireNode:public Node
{
public:

    WireNode(QString id,   Node*);

    WireNode(PinNode *pinNode);

    WireNode();
    //! уникальное имя жгута
    //QString idNameCoord;
    //! имя типа провода
    QString typeWire()
    {
        PinNode* pinNode =  static_cast<PinNode* > (parent);
        if(parent!=nullptr)
            return pinNode->strTypeWire;
        else
            return QString("");
    }
    //! длинна провода, м
    float length;
    //! указывает на контакт
    Node *toPin;
    //! признак полного соединения(т.е данный wire указаывает на pin, в свою очередь
    bool fullConnected;
    virtual Node* clone();
    virtual int type() const {return Node::E_WIRE;}
};

#endif // PINNODE_H
