#ifndef COORD_NODE_H
#define COORD_NODE_H
#include "Node.h"
#include <stdint.h>
#include "WireNode.h"

//! класс описания информационного интерфейса
class CoordNode
{
public:

    CoordNode(QString strSetCoord_);
    //! добавление контакта в интерфейс
    void addWireToCoord(WireNode* );
    QString preStr;
    int num;
    //! массив пинов, которые входят в интерфейс
    QList<WireNode*> wires;
    QString strSetCoord;
    //! тип интерфейса
   // PinNode::TYPE_INTERFACE type_interface; //! Arinc-429, РК, питание
};

#endif // PINNODE_H
