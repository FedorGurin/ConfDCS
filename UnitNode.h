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
    //! идентификатор блока расположения
    QString idUnitLocation;

    //! блок в котором контруктивно распологается данный блок(если nullptr, значит объект вверхнего уровня)
    UnitNode *parentUnit;
    QList<Node* > childUnit;// дочерние элементы
    //! признак стендового набора оборудования
    bool isStend;
    //! признак того, что блок может пропускать линии данных через себя
    bool isTransit;

    QString alias;
    //! отображение клемм друг-на-друга(или здесь возможно должна быть dll)
    //QMap<PinNode*,QList<PinNode* > > mapPin;
    //! библиотека обеспечивающая внутреннию логику
    QLibrary libMap;
    //! клонирование узла
    virtual Node *clone();
    virtual ~UnitNode();
};

#endif /* PMODULE_H_ */
