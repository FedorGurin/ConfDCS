#ifndef PINNODE_H
#define PINNODE_H
#include "Node.h"
#include <stdint.h>
//! класс описания контакта на разъеме
class PinNode:public Node
{
public:
    enum TYPE_IO
    {
        E_UNDEF_IO  ,   //! не определен
        E_BI        ,   //! двунаправленная связь
        E_IN        ,   //! входная связь
        E_OUT       ,   //! выходная связь
        E_GROUND    ,   //! заземление
        E_SHIELD    ,   //! экран
        E_CTRL          //! контроль

    };
    enum TYPE_INTERFACE
    {
        E_UNDEF_INTER   ,//!  не определен/неизвестен
        E_TEST          ,//!  для измерений или контроля
        E_ARINC_429     ,//!  Arinc429
        E_RK            ,//!  РК
        E_POWER         ,//!  питание
        E_ANALOG        ,//!  аналог
        E_RS_422        ,//!  RS-422
        E_SOUND         ,//!  звук
        E_RS_232        ,//!  RS-232
        E_ARINC_717     ,//!  Arinc-717
        E_PWM           ,//!  ШИМ
        E_VHF           ,//!  высокочастотный сигнал
        E_ETHERNET      ,//!  Ethernet
        E_ARINC_646     ,//!  Arinc646
        E_GROUND_I      ,//!  Земля
        E_SHEILD        ,
        E_PPS            //! метка единного времени
    };
    PinNode(QString id,
            QString strSignal,
            QString strIo,
            QString strNumClone,
            QString sw,
            QString strLabel,
            QString strTypeWire,
            QString strI,
            QString strSetI,
            QString strCircuit,
            QString strCord,
            QString strTypeWirePin_,
            QString strIDWire_,
            Node*);
    PinNode();
    //! название сигнала
    QString nameSignal;
    //! строка вход/выход
    QString strIO;
    //! строка с интерфейсом
    QString strInterface;
    //! стрjка кол-во размножений
    QString strNumClone;
    //! строка коммутируемый сигнал или нет
    QString strSw;
    //! название бирки
    QString strLabel   ;
    //! название интерфейса
    QString strTypeI   ;
    //! преобразованное название интерфейса (уникальный префикс)
    QString prefTypeI;
    //! название типа бирки
    QString strTypeWire;
    //! тип жилы провода
    QString strTypeWirePin;
    //! идентификатор провода
    QString strIDWire;
    //! имя жгута
    QString strCord;
    //! номер схемы
    QStringList strCircuit;
    //! тип интерфейса
    TYPE_INTERFACE type_interface; //! Arinc-429, РК, питание
    //! признак того, что сигнал коммутируется
    bool switched;
    //! кол-во размножений сигнала, 0 - не используемый контакт
    quint8 numClone;
    //! направление обмена данными
    TYPE_IO  io;
    virtual Node *clone();
    //! ссылки из дургих
    ///QList<Node* > wires;
    ///

    virtual int type() const {return Node::E_PIN;}
};

#endif // PINNODE_H
