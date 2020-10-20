#include "PinNode.h"
#include "WireNode.h"
#include "SystemNode.h"

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

    if(strInterface_.toLower() == "arinc 429")
        type_interface = E_ARINC_429;
    if(strInterface_.toLower() == "питание" )
        type_interface = E_POWER;
    if(strInterface_.toLower() == "рк" )
        type_interface = E_RK;
    if(strInterface_.toLower() == "аналог" )
        type_interface = E_ANALOG;
    if(strInterface_.toLower() == "звук" )
        type_interface = E_SOUND;
    if(strInterface_.toLower() == "rs-232" )
        type_interface = E_RS_232;
    if(strInterface_.toLower() == "rs-422" )
        type_interface = E_RS_422;
    strInterface    = strInterface_;
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
