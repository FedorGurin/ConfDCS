#ifndef UNITNODE_H_
#define UNITNODE_H_

#include <QStringList>
#include "Node.h"
#include "InterfaceNode.h"
#include "CoordNode.h"
#include <QLibrary>
//! класс описания блока
class UnitNode :public Node
{
public:
    UnitNode (QString,Node *);
    UnitNode();

    //! тип объекта
    virtual int type()const{return Node::E_UNIT;}
    //! поиск инетерфейсов
    void scanInterface(Node *startNode);
    //! поиск жгутов
    void scanCoords(Node *startNode);
    //! поиск предыдущих интерфейсов
    int findPrevInterface(PinNode *,InterfaceNode *ifNode);
    //!
    void calcInterface();
    //! список интерфейсов
    QList<InterfaceNode *> interfaces;
    //! список интерфейсов
    QList<InterfaceNode *> unknownInf;
    //! список жгутов
    QList<CoordNode *> coords;
    //! место расположение
    QString strLocation;
    //! признак стендового набора оборудования
    bool isStend;

    //! отображение клемм друг-на-друга(или здесь возможно должна быть dll)
    //QMap<PinNode*,QList<PinNode* > > mapPin;
    //! библиотека обеспечивающая внутреннию логику
    QLibrary libMap;
    //! клонирование узла
    virtual Node *clone();
    virtual ~UnitNode();
};

#endif /* PMODULE_H_ */
