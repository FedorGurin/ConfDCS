
#include "unitNode.h"
#include "./globalFunc/gl_func.h"

UnitNode::UnitNode(QString value,Node *parent):Node()
{
    rootInternal  = 0;
    idName      = value;
    pathName    = idName;
    rootInternal = nullptr;
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

    nameInternalFile.clear();
    if(class_ != "-")
        nameInternalFile = class_;
    rootInternal = 0;
    alias.clear();
    nameCoord.clear();
    rootInternal = nullptr;
    idParentSys  = p_sys_;

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
    rootInternal = nullptr;
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
bool UnitNode::recCheckConnectedPin(QPair<PinNode *, PinNode *> p, PinNode *pin)
{

//    if(pin == pin1)
//        recCheckConnectedPin()

    return true;

}
PinNode* UnitNode::findSameConnection(PinNode *pin)
{
    PinNode *curPin = pin;
    for(auto i : pins_internal)
    {
        PinNode *pin1 = i.first;
        PinNode *pin2 = i.second;

        if(curPin == pin1)
            curPin = pin2;
        else if(curPin == pin2)
            curPin = pin1;

        WireNode *wire = nullptr;
        if(curPin->child.isEmpty() == true)
            wire = new WireNode(curPin->strLabel,curPin->strTypeI,curPin);
        else
            wire = static_cast<WireNode* > (curPin->child.first());

        if(wire->fullConnected == false && curPin->type_interface != PinNode::E_TEST)
            return curPin;
    }
    return nullptr;
}
bool UnitNode::checkConnectedPins(PinNode * pin)
{
    PinNode *curPin = pin;
    for(auto i : pins_internal)
    {
        PinNode *pin1 = i.first;
        PinNode *pin2 = i.second;

        if(curPin == pin1)
            curPin = pin2;
        else if(curPin == pin2)
            curPin = pin1;

        if(curPin->child.isEmpty())
            continue;
        WireNode* wire = static_cast<WireNode* > (curPin->child.first());
        if(wire->fullConnected == true)
            return true;
    }
    return false;
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
    rootNode->nameInternalFile = this->nameInternalFile;
    rootNode->rootInternal     = this->rootInternal;


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
            InterfaceNode *intf = new InterfaceNode(pin->strTypeI,pin->type_interface,pin->strInterface);
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
        PinNode *pin = static_cast<PinNode *> (wire->parent);
        for(auto j :coords)
        {
            if(j->strSetCoord == pin->strCord)
            {
                j->addWireToCoord(wire);
                find = true;
                break;
            }
        }
        if(find == false)
        {
            CoordNode *c = new CoordNode(pin->strCord);
            coords.push_back(c);
            c->addWireToCoord(wire);
        }

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
