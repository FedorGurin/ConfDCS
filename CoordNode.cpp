#include "CoordNode.h"


//InterfaceNode::InterfaceNode(QString id,       // идентификатор интерфейса
//                             QString strSetI,  // настроки интерфейса
//                             Node *parent):Node()
//{
//    if(id.toLower() == "arinc 429")
//        type_interface = E_ARINC_429;
//    if(id.toLower() == "питание" )
//        type_interface = E_POWER;
//    if(id.toLower() == "рк" )
//        type_interface = E_RK;
//    if(id.toLower() == "аналог" )
//        type_interface = E_ANALOG;
//    if(id.toLower() == "звук" )
//        type_interface = E_SOUND;
//    if(id.toLower() == "rs-232" )
//        type_interface = E_RS_232;
//    if(id.toLower() == "rs-422" )
//        type_interface = E_RS_422;
//    idName      = id;
//    pathName    = idName;

//    parent->addChild(this);
//    addParent(parent);
//}
CoordNode::CoordNode(QString strSetCoord_)
{
    strSetCoord         = strSetCoord_;
    preStr          = "";
    //type_interface  = type;
    num = 0;
}

void CoordNode::addWireToCoord(WireNode* pin)
{
    wires.push_back(pin);
}
//Node *InterfaceNode::clone()
//{
//    InterfaceNode *rootNode = new InterfaceNode;

////    rootNode->idName        = this->idName;
////    rootNode->displayName   = this->displayName;
////    rootNode->comment       = this->comment;
////    rootNode->pathName      = this->pathName;

////    rootNode->io            = this->io;
////    rootNode->numClone      = this->numClone;
////    rootNode->nameSignal    = this->nameSignal;
////    rootNode->switched      = this->switched;
////    rootNode->type_interface= this->type_interface;

////   rootNode->strIO        = this-> strIO       ;
////   rootNode->strInterface = this-> strInterface;
////   rootNode->strNumClone  = this-> strNumClone ;
////   rootNode->strSw        = this-> strSw       ;
////   rootNode->strLabel     = this-> strLabel    ;
////   rootNode->strTypeI     = this-> strTypeI    ;
////   rootNode->strTypeWire  = this-> strTypeWire ;
////   rootNode->strCircuit   = this-> strCircuit ;
////    for(auto i:child)
////    {
////        Node* new_node = i->clone();
////        rootNode->addChild(new_node);
////    }
//    return rootNode;
//}
