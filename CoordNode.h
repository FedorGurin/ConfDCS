#ifndef COORD_NODE_H
#define COORD_NODE_H
#include "Node.h"
#include <stdint.h>
#include "PinNode.h"

//! класс описания информационного интерфейса
class CoordNode
{
public:

    CoordNode(QString strSetI_,PinNode::TYPE_INTERFACE type);
    //! добавление контакта в интерфейс
    void addPinToInterface(PinNode* );
    QString preStr;
    int num;
    //! массив пинов, которые входят в интерфейс
    QList<PinNode*> pins;
    QString strSetI;
    //! тип интерфейса
    PinNode::TYPE_INTERFACE type_interface; //! Arinc-429, РК, питание 
};

#endif // PINNODE_H
