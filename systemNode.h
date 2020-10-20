#ifndef SYSTEMNODE_H
#define SYSTEMNODE_H
#include "Node.h"
#include <stdint.h>
//! класс для описания системы блоков
class SystemNode:public Node
{
public:
    SystemNode(QString,      Node*);
    SystemNode();
    //! глубокое клонирование объекта
    virtual Node* clone();

    virtual int type() const {return Node::E_SYSTEM;}
};

#endif // GROUPLABEL_H
