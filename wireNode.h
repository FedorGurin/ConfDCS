#ifndef WIRENODE_H
#define WIRENODE_H
#include "Node.h"
#include <stdint.h>
#include "pinNode.h"
//! класс объединения одинаковых полей
class WireNode:public Node
{
public:

    WireNode(QString id,
             QString type,
            // QString idName_,
             Node*);

    WireNode(PinNode *pinNode)
    {
        WireNode(pinNode->strLabel,pinNode->strTypeWire,pinNode);
    }
    WireNode();
    //! уникальное имя жгута
    //QString idNameCoord;
    //! имя типа провода
    QString typeWire;
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
