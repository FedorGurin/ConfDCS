#ifndef UNITNODE_H_
#define UNITNODE_H_

#include <QStringList>
#include "Node.h"
#include "InterfaceNode.h"
#include "CoordNode.h"
#include <QLibrary>
#include <QPair>
#include <pinNode.h>
//! класс описания блока
class UnitNode :public Node
{
public:
    UnitNode (QString,Node *);
    UnitNode (QString fName_,
              QString sName_,
              QString stend_,
              QString install_,
              QString trans_,
              QString id_,
              QString loc_,
              QString p_sys_,
              QString size_,
              QString pos_,
              QString class_,
              QString alias_,
              QString nameCoord_,
              Node* node);
    UnitNode();

    //! тип объекта
    virtual int type()const{return Node::E_UNIT;}
    //! поиск инетерфейсов
    void scanInterface(Node *startNode);
    //! поиск жгутов(сборка проводов в жгуты по указанным идентификаторам жгутов)
    void scanCoords(Node *startNode);
    void renameCoords(Node *startNode);
    //! поиск предыдущих интерфейсов
    int findPrevInterface(PinNode *,InterfaceNode *ifNode);
    //!
    void calcInterface();
    //! проверка, что node имеет уже подключение (или подключение через другие клеммы)
    bool checkConnectedPins(PinNode *pin);
    bool recCheckConnectedPin(QPair<PinNode *, PinNode *> p, PinNode *pin);
    //! поиск свободного контакта имеющего внутренее соединение с контактом \param node
    PinNode* findSameConnection(PinNode *pin, PinNode::TYPE_IO type = PinNode::TYPE_IO::E_BI);
    //! список контактов имеющих внутренее соединение с указаным \param node
    QList<PinNode* > findAllInternalConnection(PinNode *node);
    //! список интерфейсов
    QList<InterfaceNode *> interfaces;
    //! список интерфейсов
    QList<InterfaceNode *> unknownInf;
    //! список жгутов
    QList<CoordNode *> coords;
    //! идентификатор блока расположения
    QString idUnitLocation;
    QString idParentSys;

    //! дерево описывающее детализацию данного блока
    Node *rootInternal;

    //UnitNode *parentUnit;
    //QList<Node* > childUnit;// дочерние элементы
    //! признак стендового набора оборудования
    bool isStend;
    //! признак того, что блок может пропускать линии данных через себя
    bool isTransit;
    //! псевдоним блока для именования бирок
    QString alias;
    QString nameCoord;
    //! имя файла с описанием внутренних параметров
    QString nameInternalFile;
    //! отображение клемм друг-на-друга(или здесь возможно должна быть dll)
    //QMap<PinNode*,QList<PinNode* > > mapPin;
    //! библиотека обеспечивающая внутреннию логику
    QLibrary libMap;
    //! таблица соединений контактов внутри блока
    QVector<QPair<PinNode *, PinNode * > > pins_internal;
    //! клонирование узла
    virtual Node *clone();
    virtual ~UnitNode();
};

#endif /* PMODULE_H_ */
