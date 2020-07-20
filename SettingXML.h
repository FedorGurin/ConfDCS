#ifndef SETTINGXML_H
#define SETTINGXML_H
#include <QString>
#include <QVector>
#include <QHostAddress>
#include <stdint.h>
//! описание вычислительного узла
typedef struct TVNode_
{
    int id;         //! уникальный идентификатор
    QString nameId; //! название узла
    QHostAddress addr;
}TVNode;

//! модуль для считывания настроечных параметров их xml
class SettingXML
{
public:
    SettingXML();
    //! ip - адрес текущего компютера
    QString ip_main_prog;
    //! ip - адрес УЦВС
    QString ip_target;
    //название архива с описанием данных
    QString path7zipFile;
    QHostAddress addr_target;
    //! название файла с данными
    QString fileData;
    QString dataDir;    
    //! порты для взаимодействия с графическим интерфейсом
    uint16_t send_port;
    uint16_t recive_port;
    //! размер шрифта
    int sizeFont;
    QString pathToFtp;
    QString userFtp;
    QString passwordFtp;
    QString uploadFileNameFTP;
    //! поиск IP по уникальному идентфикатору
    QHostAddress findIp(int idNode)
    {
        if (idNode == 0 || listVNode.isEmpty() == true)
            return addr_target;

        for (int i = 0; i<listVNode.size(); i++)
        {
            if(listVNode[i].id == idNode)
                return (listVNode[i].addr);
        }
        return QHostAddress();
    }
    QVector<QHostAddress> findAllIp()
    {
        QVector<QHostAddress> addr;

        if(listVNode.isEmpty() == true)
            addr.push_back(addr_target);

        for (auto node: listVNode)
        {
            addr.push_back(node.addr);          
        }
        return addr;
    }

    //! выравнивание по кол-ву байт
    int allign;
    //! получить указатель на статический объект
    static SettingXML* getObj();
private:
    static SettingXML *setting;
    //! список узлов вычислтелей
    QVector<TVNode> listVNode;
};

#endif // SETTINGXML_H
