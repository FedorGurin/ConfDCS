#include "pinNode.h"
#include "wireNode.h"
#include "systemNode.h"

PinNode::PinNode(QString id,
                 QString strSignal_,
                 QString strIo_,
                 QString strNumClone_,
                 QString strSw_,
                 QString strLabel_,
                 QString strTypeWire_,
                 QString strInterface_,
                 QString strTypeI_,
                 QString strCircuit_,
                 QString strCord_,
                 QString strTypeWirePin_,
                 QString strIDWire_,
                 Node *parent):Node()
{
    io = E_UNDEF_IO;
    if(strIo_.toLower() == "прием")
        io = E_IN;

    if(strIo_.toLower() == "выдача")
        io = E_OUT;

    if(strIo_.toLower() == "прием/выдача" || strIo_.toLower() == "выдача/прием")
        io = E_BI;

    if(strIo_.toLower() == "заземление" || strIo_.toLower() == "земля")
        io = E_GROUND;

    if(strIo_.toLower() == "экран")
        io = E_SHIELD;
    strIO = strIo_.toLower();
    type_interface = E_UNDEF_INTER;

    strInterface    = strInterface_;

    if(strInterface.contains("arinc 429", Qt::CaseInsensitive))
        type_interface = E_ARINC_429;
    if(strInterface.contains("питание", Qt::CaseInsensitive))
        type_interface = E_POWER;
    if(strInterface.contains("рк", Qt::CaseInsensitive))
        type_interface = E_RK;
    if(strInterface.contains("аналог", Qt::CaseInsensitive))
        type_interface = E_ANALOG;
    if(strInterface.contains("звук", Qt::CaseInsensitive))
        type_interface = E_SOUND;
    if(strInterface.contains("rs-232", Qt::CaseInsensitive))
        type_interface = E_RS_232;
    if(strInterface.contains("rs-422", Qt::CaseInsensitive))
        type_interface = E_RS_422;
    if(strInterface.contains("arinc 646", Qt::CaseInsensitive))
        type_interface = E_ARINC_646;
    if(strInterface.contains("шим", Qt::CaseInsensitive))
        type_interface = E_PWM;
    if(strInterface.contains("корпус", Qt::CaseInsensitive))
        type_interface = E_GROUND_I;

    nameSignal      = strSignal_;
    strNumClone     = strNumClone_;
    strSw           = strSw_;
    strLabel        = strLabel_;
    strTypeI.clear();
    if(strTypeI_ !="-")
         strTypeI        = strTypeI_;

    strIDWire.clear();
    if(strIDWire_ != "-")
        strIDWire = strIDWire_;

    strTypeWirePin.clear();
    if(strTypeWirePin_ != "-")
        strTypeWirePin = strTypeWirePin_;

    strCord.clear();
    if(strCord_ != "-")
        strCord = strCord_;

    strTypeWire.clear();

    if(strTypeWire_ != "-")
        strTypeWire     = strTypeWire_;

    if(strTypeI == "-")
        strTypeI = nameSignal;
    strCircuit.append(strCircuit_);

    numClone    = strNumClone_.toInt();
    idName      = id;
    if(strSw_.toLower() == "да")
        switched    = true;
    else
        switched    = false;

    pathName    = idName;

    prefTypeI ="";

    parent->addChild(this);
    addParent(parent);
    for(int i = 0;i < numClone;i++)
    {
        if(strLabel_ != "-")
            new WireNode(strLabel_,strTypeWire_,strCord,this);
    }
}
PinNode::PinNode():Node()
{
    io = E_UNDEF_IO;
     prefTypeI ="";
}
Node *PinNode::clone()
{
    PinNode *rootNode = new PinNode;

    rootNode->idName        = this->idName;
    rootNode->displayName   = this->displayName;
    rootNode->comment       = this->comment;
    rootNode->pathName      = this->pathName;

    rootNode->io            = this->io;
    rootNode->numClone      = this->numClone;
    rootNode->nameSignal    = this->nameSignal;
    rootNode->switched      = this->switched;
    rootNode->type_interface= this->type_interface;

   rootNode->strIO        = this-> strIO       ;
   rootNode->strInterface = this-> strInterface;
   rootNode->strNumClone  = this-> strNumClone ;
   rootNode->strSw        = this-> strSw       ;
   rootNode->strLabel     = this-> strLabel    ;
   rootNode->strTypeI     = this-> strTypeI    ;
   rootNode->strTypeWire  = this-> strTypeWire ;
   rootNode->strCircuit   = this-> strCircuit ;
   rootNode->prefTypeI    = this-> prefTypeI;
   rootNode->strCord      = this->strCord;
    for(auto i:child)
    {
        Node* new_node = i->clone();
        rootNode->addChild(new_node);
    }
    return rootNode;
}
