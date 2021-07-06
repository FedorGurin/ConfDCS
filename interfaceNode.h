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
    QString displayName;
    //! идентификатор
    uint32_t idNode;
    //! тип канала
    QString type;
    QString typeRK;

    //! имя перечисления
    QString enumStr;
    //! прием/выдача
    uint8_t io;
    //! прием/выдача
    QString ioStr;
    //! Скорость передчи
    QString bitrate;
    //! паузу между словами
    QString period;
    //! идентификатор подключенного модуля
    QString idConnectedUnit;
    //! откуда скопировать данные
    QString copyFrom;
    //! циклограмма выдачи
    QVector<int> addrs;
    //! Описание данных в файлах
    QStringList fileNames;
    //! признак того, что данный канал нужно пропустить
    uint8_t skip;
}TCh;
//! описание одного параметра
typedef struct TParam_
{
    QString idName;
    QString fullName;
    QString units;
    int addr;
    QString hiBit;
    QString lowBit;
    QString csr;
    QString cmr;
    QString sign;
    uint8_t s;
    QString label;
    QString enumCh;
    QString enumParam;
    QString enumPack;
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
    //! \todo Нужно сделать одну функцию (это дублирующая функция)
    bool openFileParams(const QString &nameFile);

    //! описание канала
    TCh ch;
    //! список параметров
    QVector<TParam> params;
    //! тип интерфейса
    PinNode::TYPE_INTERFACE type_interface; //! Arinc-429, РК, питание 
};

#endif // PINNODE_H
