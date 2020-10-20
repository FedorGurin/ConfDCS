#include "settingXML.h"
#include "./globalFunc/gl_func.h"
#include <QFile>
#include <QApplication>
//! ip-адреса по умолчанию
#define IP "127.0.0.1"
#define IP_MAIN_PROG "127.0.0.1"
//! порты по умолчанию
#define SEND_PORT 4800
#define RECIVE_PORT 4801
//! порт приема от подчиненной копии программы
#define RECIVE_PORT_SLAVE 4802
#define SEND_PORT_SLAVE 4803
//! имя файла по умолчанию
#define DATA_FILE "data.xml"

//! инициализация статического объекта
SettingXML* SettingXML::setting = nullptr;

SettingXML* SettingXML::getObj()
{
    if(setting == nullptr)
        setting = new SettingXML();
    return setting;
}

SettingXML::SettingXML()
{
    sizeFont    = -1;
    allign      = 0;

    ip_main_prog = readParamFromXMLFile(nameMainFile,"MPPM","IP");
    if(ip_main_prog.isEmpty() == true)
        ip_main_prog = IP_MAIN_PROG;

    ip_target = readParamFromXMLFile(nameMainFile,"MPPM","IP_TARGET");
    if(ip_target.isEmpty() == true)
        ip_target = IP;

    userFtp = readParamFromXMLFile(nameMainFile,"FTP","USER");
    if(userFtp.isEmpty() == true)
        userFtp = "fedor";

    passwordFtp = readParamFromXMLFile(nameMainFile,"FTP","PASSWORD");
    if(passwordFtp.isEmpty() == true)
        passwordFtp = "bellman";

    pathToFtp = readParamFromXMLFile(nameMainFile,"FTP","PATH");
    if(pathToFtp.isEmpty() == true)
        pathToFtp = "ftp://192.168.1.1/My_Book/Data/dataBase.7z";

    uploadFileNameFTP = readParamFromXMLFile(nameMainFile,"FTP","OUTPUT");
    if(uploadFileNameFTP.isEmpty() == true)
        uploadFileNameFTP = "d:/Test/dataBase.7z";


    fileData = readParamFromXMLFile(nameMainFile,"MPPM","DATA_FILE");
    if(fileData.isEmpty() == true)
        fileData = DATA_FILE;

    dataDir = readParamFromXMLFile(nameMainFile,"MPPM","DATA_DIR");
    if(dataDir.isEmpty() == true)
    {
        dataDir = readParamFromXMLFile(nameMainFile,"MPPM","DATA_DIR_LOCAL");
        if(dataDir.isEmpty() == true)
            dataDir = qApp->applicationDirPath();
    }    
    send_port = readParamFromXMLFile(nameMainFile,"MPPM","SEND_PORT").toInt();
    if(send_port == 0)
        send_port = SEND_PORT;

    recive_port = readParamFromXMLFile(nameMainFile,"MPPM","RECIVE_PORT").toInt();
    if(recive_port == 0)
        recive_port = RECIVE_PORT;

    sizeFont = readParamFromXMLFile(nameMainFile,"MPPM","SIZE_FONT").toInt();
    if(sizeFont == 0)
        sizeFont = 0;

    addr_target.setAddress(ip_target);

    //! чтение существующих узлов
    QFile file(qApp->applicationDirPath()+"/"+nameMainFile);
    file.open(QIODevice::ReadOnly);

    QDomDocument d;
    d.setContent(&file);
    QDomElement node = d.documentElement();
    node = node.firstChildElement("MPPM_VNODE");

    while (!node.isNull())
    {
        if(node.isNull() == false)
         {
             TVNode vnode;

             vnode.id     = node.attribute("Id",     "0").toInt();
             vnode.addr.setAddress(node.attribute("Ip",     "127.0.0.1"));
             vnode.nameId = node.attribute("NameId", "");
             listVNode.push_back(vnode);
         }

         node = node.nextSiblingElement("MPPM_VNODE");

    }
}
