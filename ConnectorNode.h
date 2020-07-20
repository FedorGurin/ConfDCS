#ifndef CONNECTOR_NODE_H_
#define CONNECTOR_NODE_H_

#include "Node.h"

//! класс описания разъема(разъем должен содержать два множества)
class ConnectorNode: public Node{
public:
    //! конструктор
    ConnectorNode(QString id,
                  QString typeConBlock,
                  QString typeConWire,
                  Node* );
    ConnectorNode();

    //! тип узла
    virtual int type() const {return Node::E_CONNECTOR;}

    virtual Node *clone();
    //! тип разъема
    QString typeConnectorBlock;
    QString typeConnectorWire;
    //! соединен со следующим разъемом
    ConnectorNode *connetWith;
    //! деструктор
    virtual ~ConnectorNode();
};
#endif /* CONNECTORNODE_H_ */
