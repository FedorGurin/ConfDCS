#ifndef NODE_H_
#define NODE_H_

#include <QString>
#include <QList>
#include <QVector>
#include <QModelIndex>
#include <QObject>
#include <stdint.h>

class Node
{
public:
    Node(QString nameId = "");
    //! тип узла
    enum Type{E_EMPTY       , // узел не определен
              E_SYSTEM      , // система
              E_UNIT        , // блок
              E_CONNECTOR   , // разъем              
              E_LOCATION    ,
              E_PIN         , // контакт
              E_WIRE        , // провод соединения
              E_INTERFACE   };// информационный интерфейс

//имя которое будет отображаться пользователю
    QString displayName;
    //! имя идентификатор
    QString idName;
//    //! псевдоним
//    QString alias;
    //! комментарий к узлу
    QString comment;
    //! имя пути к данному узлу
    QString pathName;
    //! Признак отображать пользователю данный узел или нет(true - )
    bool isDisplay;
    static quint64 countId;
    quint64 id;

     void calcInterface();
    //! найти видимый узел по порядковому номеру
    Node * findDispayNode(int index)
    {
        int i = -1;
        for(auto node : child)
        {
            if(node->isDisplay == true)
                i++;
            if(index == i)
                return node;
        }

        return nullptr;
    }
    int sizeDisplayNodes()
    {
        int size = 0;
        for(auto node : child)
        {
            if(node->isDisplay == true)
                size ++;
        }
        return size;
    }
    //! добавить родителя
    void addParent(Node* p)
    {
        parent   = p;
    }
    //! добавить потомка
    virtual void addChild(Node* ch)
    {
        ch->parent = this;
        if(child.isEmpty() == false)
        {
            ch->left        = child.last();
            ch->left->right = ch;
        }

        child.push_back(ch);
        if(this->pathName.isEmpty() == false)
        ch->pathName = this->pathName+"." + ch->pathName;
    }
    void addModelIndex(QModelIndex i, int column)
    {
        if(column>=index.size())
        {
            index.resize(column+1);
        }
        index[column]=i;
    }
    QModelIndex modelIndexByCol(int column)
    {
        return index[column];
    }

    Node *parent;//родителький элемент

    Node *left; //элемент левее
    Node *right;//элемент правее

    Node* leftNode()// вернуть узел слева
    {
        return left;
    }
    Node* rightNode()//вернуть узел справа
    {
        return right;
    }
    //! глубокое клонирование объекта
    virtual Node* clone();

    QList<Node* > child;// дочерние элементы
    QVector<QModelIndex> index;

    virtual int type()const{return E_EMPTY;}
    virtual ~Node();


};

#endif /* NODE_H_ */
