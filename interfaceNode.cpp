#include "interfaceNode.h"
#include <QJsonArray>
#include <QFile>

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
InterfaceNode::InterfaceNode(QString strSetI_,PinNode::TYPE_INTERFACE type,QString strInterface)
{
    strSetI         = strSetI_;
    strTypeInerface = strInterface;
    preStr          = "";
    type_interface  = type;
    num = 0;
}
InterfaceNode::InterfaceNode(QJsonObject &json)
{
    bool tr;
    ch.id               = json["idCh"].toString().toUInt();
    ch.io               = json["io"].toString() == "выдача";
    if(ch.io == 1)
        ch.ioStr = "E_CH_IO_OUTPUT";
    else
        ch.ioStr = "E_CH_IO_INPUT";
    if(json["typeCh"].toString() == "AR429")
        ch.type = "E_CH_AR";
    else if(json["typeCh"].toString().contains("RK",Qt::CaseInsensitive) == true)
        ch.type = "E_CH_RK";
    else if(json["typeCh"].toString() == "IR")
        ch.type = "E_CH_IR";
    else if(json["typeCh"].toString() == "DAC")
        ch.type = "E_CH_DAC";
    else if(json["typeCh"].toString() == "ITP")
        ch.type = "E_CH_ITP";
    else if(json["typeCh"].toString() == "IP")
        ch.type = "E_CH_IP";
    else if(json["typeCh"].toString() == "GEN_NU")
        ch.type = "E_CH_GEN_NU";
    else if(json["typeCh"].toString() == "GEN")
            ch.type = "E_CH_GEN";
    ch.typeRK.clear();
    if(ch.type == "E_CH_RK")
    {
        if(json["typeCh"].toString().contains("1",Qt::CaseInsensitive) == true)
            ch.typeRK = "Тип 1";
        else if(json["typeCh"].toString().contains("2",Qt::CaseInsensitive) == true)
            ch.typeRK = "Тип 2";
        else
            ch.typeRK = "Не определена";

    }
    //ch.type             = json["typeCh"].toString();
    ch.idName           = json["idName"].toString().toUpper();
    if(ch.idName =="-")
        ch.idName.clear();


    ch.displayName      = json["displayName"].toString();
    ch.typeNode         = json["typeNode"].toString();
    ch.idNode           = json["idNode"].toString().toUInt();
    ch.idConnectedUnit  = json["connectToSys"].toString().toUpper();
    ch.copyFrom         = json["copyFrom"].toString();
    if(ch.type == "E_CH_AR")
    {
        ch.bitrate          = json["bitrate"].toString();
        ch.period           = json["period"].toString();
    }


    if(json.contains("addrs") && json["addrs"].isArray())
    {
        QJsonArray addrArray = json["addrs"].toArray();
        for(int k = 0; k< addrArray.size(); k++)
        {
            QJsonObject kArray = addrArray[k].toObject();
            QString addr = kArray["addr"].toString();
            ch.addrs.append(addr.toInt(&tr,8));
        }
    }
    if(json.contains("files") && json["files"].isArray())
    {
        QJsonArray filesArray = json["files"].toArray();
        for(int k = 0; k< filesArray.size(); k++)
        {
            QJsonObject kArray = filesArray[k].toObject();
            QString fileName = kArray["fileName"].toString();
            ch.fileNames.append(fileName);
            openFileParams(fileName);
        }
    }


}
bool InterfaceNode::openFileParams(const QString &nameFile)
{
    bool ok = true;


    QFile file("./csv/protocols/" + nameFile);
    bool openFile =  file.open(QIODevice::ReadOnly | QIODevice::Text);
    // создаем корень структуры
    if(openFile == true)
    {
        QString errMsg  = "";
        QTextStream in(&file);
        in.setCodec("UTF-8");
        QString line = in.readLine();
        while(line.isEmpty() == false)
        {
            line = in.readLine();
            if(line.isEmpty())
                continue;
            QStringList listLine = line.split(";", QString::SkipEmptyParts);
            if(listLine[0] == "Название идентификатора")
                continue;

            bool isOct;
            TParam param;
            param.idName   = listLine[0];
            param.fullName = listLine[1];
            param.units    = listLine[2];
            param.addr     = listLine[3].toInt(&isOct,8);

            param.hiBit    = listLine[4];
            param.lowBit   = listLine[5];

            param.csr      = listLine[6];
            if(listLine[6] == "-")
                param.csr.clear();
            param.cmr      = listLine[7];
            if(param.cmr == "-")
                param.cmr.clear();
            param.sign     = listLine[8];
            if(param.sign.toLower() == "да")
                param.s = 1;
            else
                param.s = 0;

            param.label    = listLine[9];
            if(param.label == "-")
                param.label.clear();
            params.append(param);
        };
        file.close();
    }

    return ok;
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
