#ifndef INTERFACE_NODE_H
#define INTERFACE_NODE_H
#include "Node.h"
#include <stdint.h>
#include "PinNode.h"
#include <QJsonObject>
//#include "InterfaceParam.h"
//! описание канала
typedef struct TCh_
{
    //! идентификатор канала
    uint32_t id;
    //! название канала
    QString idName;
    //! тип узла
    QString typeNode;
    //! идентификатор
    uint32_t idNode;
    //! тип канала
    QString type;
    //! прием/выдача
    uint8_t io;
    //! идентификатор подключенного модуля
    QString idConnectedUnit;
    //! циклограмма выдачи
    QVector<QString> addrs;
}TCh;
//! описание одного параметра
typedef struct TParam_
{
    QString idName;
    QString fullName;
    QString units;
    QString addr;
    QString hiBit;
    QString lowBit;
    QString csr;
    QString cmr;
    QString sign;
    QString label;
}TParam;
//! класс описания информационного интерфейса
class InterfaceNode//:public Node
{
public:

    InterfaceNode(QString strSetI_,PinNode::TYPE_INTERFACE type,QString strInterface);
    InterfaceNode(QJsonObject &json);
    //! добавление контакта в интерфейс
    void addPinToInterface(PinNode* );
    QString preStr;
    //! кол-во слов
    int num;
    //! массив пинов, которые входят в интерфейс
    QList<PinNode*> pins;
    //! название интерфейса
    QString strSetI;
    //! название типа интферфейса
    QString strTypeInerface;

    //! описание канала
    TCh ch;
    //! список параметров
    QVector<TParam> params;
    //! тип интерфейса
    PinNode::TYPE_INTERFACE type_interface; //! Arinc-429, РК, питание 
};

#endif // PINNODE_H
