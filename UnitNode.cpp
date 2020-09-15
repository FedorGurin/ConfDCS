
#include "UnitNode.h"
#include "./globalFunc/gl_func.h"

UnitNode::UnitNode(QString value,Node *parent):Node()
{
    parentUnit  = 0;
    idName      = value;
    pathName    = idName;
    isStend     = false;
    isTransit   = false;
    alias.clear();
    idUnitLocation.clear();

    listForCompleter<<displayName;

    parent->addChild(this);
    addParent(parent);
}
UnitNode::UnitNode (QString fName_,
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
          Node* parent)
{
    displayName = fName_;
    idName = id_;
    isStend = (stend_.toLower() == "да");
    isTransit = (trans_.toLower() == "да");

    parentUnit = 0;
    alias.clear();
    nameCoord.clear();

    if(nameCoord_ != "-")
        nameCoord = nameCoord_;

    if(alias_ !="-")
        alias = alias_;

    parent->addChild(this);
    addParent(parent);
}
UnitNode::UnitNode():Node()
{
    idUnitLocation.clear();
    isStend = false;
}
int UnitNode::findPrevInterface(PinNode *n,InterfaceNode *ifNode)
{
    int index = 0;

    for(auto i:interfaces)
    {
        if(ifNode == i)
            break;
        if(i->pins.first()->io == n->io &&
           i->pins.first()->type_interface == n->type_interface  &&
           ifNode!=i)
        {
            index ++;//i->num;
        }
    }
    return index;
}
void UnitNode::calcInterface()
{
    for(auto i: interfaces)
    {
        int index = findPrevInterface(i->pins.first(),i);
        i->num = index +1;
        i->preStr = "_[" + i->pins.first()->parent->parent->idName + "_" + i->pins.first()->strInterface + "_" +
                    i->pins.first()->strIO + "_" +
                    QString::number(i->num) + "]";
        for(auto j:i->pins)
        {
            j->prefTypeI = i->preStr;
        }
    }
}
Node *UnitNode::clone()
{
    UnitNode *rootNode = new UnitNode;

    rootNode->idName        = this->idName;
    rootNode->displayName   = this->displayName;
    rootNode->comment       = this->comment;
    rootNode->pathName      = this->pathName;
    rootNode->isStend       = this->isStend;
    rootNode->isTransit     = this->isTransit;
    rootNode->alias         = this->alias;
    rootNode->nameCoord     = this->nameCoord;


    for(auto i:child)
    {
        Node* new_node = i->clone();
        rootNode->addChild(new_node);
    }
    return rootNode;
}
void UnitNode::scanInterface(Node* startNode)
{
    bool find = false;
    if(startNode->type() == E_PIN)
    {
        PinNode *pin = static_cast<PinNode* > (startNode);
        for(auto j : interfaces)
        {
            if(j->strSetI == pin->strTypeI)
            {
                j->addPinToInterface(pin);
                find = true;
                break;
            }
        }
        if(find == false)
        {
            InterfaceNode *intf = new InterfaceNode(pin->strTypeI,pin->type_interface);
            interfaces.push_back(intf);
            intf->addPinToInterface(pin);
        }
        return;
    }
    for(auto i:startNode->child)
    {
        scanInterface(i);
    }
}
void UnitNode::scanCoords(Node* startNode)
{
    bool find = false;
    if(startNode->type() == E_WIRE)
    {
        WireNode *wire = static_cast<WireNode* > (startNode);
        for(auto j :coords)
        {
            if(j->strSetCoord == wire->idNameCoord)
            {
                j->addWireToCoord(wire);
                find = true;
                break;
            }
        }
        if(find == false)
        {
            CoordNode *c = new CoordNode(wire->idNameCoord);
            coords.push_back(c);
            c->addWireToCoord(wire);
        }
        return;
    }
    for(auto i:startNode->child)
    {
        scanCoords(i);
    }
}
UnitNode::~UnitNode()
{
    // TODO Auto-generated destructor stub
}
