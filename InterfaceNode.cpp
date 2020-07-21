#include "InterfaceNode.h"


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
InterfaceNode::InterfaceNode(QString strSetI_,PinNode::TYPE_INTERFACE type)
{
    strSetI         = strSetI_;
    preStr          = "";
    type_interface  = type;
    num = 0;
}
InterfaceNode::InterfaceNode(QJsonObject &json)
{
    ch.id               = json["idCh"].toInt();
    ch.io               = json["io"].toString() == "выдача";
    ch.type             = json["typeCh"].toString();
    ch.idName           = json["idName"].toString();
    ch.typeNode         = json["typeCh"].toString();
    ch.idNode           = json["idNode"].toInt();
    ch.idConnectedUnit  = json["connectToSys"].toString();
}
void InterfaceNode::addPinToInterface(PinNode* pin)
{
    pins.push_back(pin);
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
