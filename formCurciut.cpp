#include "formCurciut.h"
#include "ui_formCurciut.h"
#include "unitNode.h"

#include <QVector>
#include <QMessageBox>
#include "./mppm/CommonEngineData.h"
#include "./mppm/libmppm.h"
#include <QLibrary>
typedef IEngineData* (*CreateEngine)();

FormCurciut::FormCurciut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCurciut)
{
    ui->setupUi(this);
    domParser = new DomParser;


#ifdef QT_DEBUG
    QLibrary libMPPM("libmppmd");
#else
    QLibrary libMPPM("libmppm");
#endif

    CreateEngine func = reinterpret_cast<CreateEngine > (libMPPM.resolve("createEngine"));
    if(func == nullptr)
    {
        QMessageBox::warning(this, tr("Внимание!"),
                             tr("libMPPM: (CreateEngine)libMPPM.resolve(\"createEngine\") = 0. \n"
                                "Библиотека libMPPM не подключена/не загружена"),
                             QMessageBox::Ok);

    }
    //engine = func();

  //! получение обратного сигнала
//    connect(engine, SIGNAL(reciveEventsRequest(TRequestEvent)), this, SLOT(slotIds(TRequestEvent)));
//    connect(engine, SIGNAL(reciveEventsRequest(TRequestEvent)), this, SLOT(slotEventsRequest(TRequestEvent)));

    /*for(auto i:domParser->rootItemData->child[0]->child)
    {
        ui->listWidgetSys1->addItem(i->displayName);
        ui->listWidgetSys2->addItem(i->displayName);
    }*/
    connect(ui->pushButton,         SIGNAL(clicked()),this,SLOT(slotPushGen()));
    connect(ui->pushButtonDataBase, SIGNAL(clicked()),this,SLOT(slotDataBase()));
    connect(ui->pushButtonLoad,     SIGNAL(clicked()),this,SLOT(slotLoadData()));
    connect(ui->pushButtonCut,      SIGNAL(clicked()),this,SLOT(slotCut()));
    connect(ui->pushButtonRoute,      SIGNAL(clicked()),this,SLOT(slotGenRoute()));
    connect(ui->listWidgetSys1,     SIGNAL(itemSelectionChanged()),this,SLOT(slotItemSelection()));
    connect(ui->listWidgetSys2,     SIGNAL(itemSelectionChanged()),this,SLOT(slotItemSelection()));
    connect(ui->listWidgetSysMiddle,    SIGNAL(itemSelectionChanged()),this,SLOT(slotItemSelection()));
    connect(ui->listWidgetInter,    SIGNAL(itemSelectionChanged()),this,SLOT(slotItemSelectionInterfaces()));
    connect(ui->pushButtonExportRP,      SIGNAL(clicked()),this,SLOT(slotExportRP()));
    connect(ui->pushButtonGenCpp,      SIGNAL(clicked()),this,SLOT(slotGenCpp()));

}
void FormCurciut::slotGenCpp()
{
    domParser->saveChEnum();
    domParser->saveCh();
    domParser->savePackEnum();
    domParser->savePack();
    domParser->saveParamEnum();
    domParser->saveParam();
}
void FormCurciut::slotGenRoute()
{
    QList<QListWidgetItem*> listSys1      = ui->listWidgetSys1->selectedItems();
    if(listSys1.isEmpty() == false)
    {
        for(auto i: listSys1)
            domParser->saveCoordToFile(recFindNodeByName(domParser->rootItemData,i->text()));
    }else
    {
        domParser->saveCoordToFile();
    }
}
void FormCurciut::slotItemSelectionInterfaces()
{
    curInterfaces.clear();
    QList<QListWidgetItem*> listItems      = ui->listWidgetInter->selectedItems();
    for(auto i : listItems)
    {
        curInterfaces.append((PinNode::TYPE_INTERFACE)(i->data(50).toInt()));
    }
}
void FormCurciut::slotItemSelection()
{
    //! список файлов с узлами
    QVector<Node *> findNodes;

    QList<QListWidgetItem*> listSys1      = ui->listWidgetSys1->selectedItems();
    QList<QListWidgetItem*> listSys2      = ui->listWidgetSys2->selectedItems();
    QList<QListWidgetItem*> listSysMiddle = ui->listWidgetSysMiddle->selectedItems();

    ui->listWidgetInter->clear();

    if(listSys1.isEmpty() == false)
    {
        //! нужно найти все интерфейсы
        for(auto i:listSys1)
        {
            //! поиск по имени
            Node* node = recFindNodeByName(domParser->rootItemData,i->text());
            if(node != nullptr)
                findNodes.append(node);
        }
    }
    if(listSys2.isEmpty() == false)
    {
        //! нужно найти все интерфейсы
        for(auto i:listSys2)
        {
            //! поиск по имени
            Node* node = recFindNodeByName(domParser->rootItemData,i->text());
            if(node != nullptr)
                findNodes.append(node);
        }
    }
//    if(listSysMiddle.isEmpty() == false)
//    {
//        //! нужно найти все интерфейсы
//        for(auto i:listSysMiddle)
//        {
//            //! поиск по имени
//            Node* node = recFindNodeByName(domParser->rootItemData,i->text());
//            if(node != nullptr)
//                findNodes.append(node);
//        }
//    }
    actListInterfaces.clear();
    //curInterfaces.clear();
    QVector<PinNode::TYPE_INTERFACE> vec;
    for(auto i:findNodes)
    {
        if(i->type() == Node::E_UNIT)
        {
            UnitNode *unit = static_cast<UnitNode* >(i);
            for(auto j:unit->interfaces)
            {
                if(checkHasInterfaces(vec,j->type_interface) == false)
                {
                    vec.append(j->type_interface);
                    QListWidgetItem *act = new QListWidgetItem(j->strTypeInerface);
                    actListInterfaces.append(act);
                    act->setData(50,j->type_interface);
                }
            }
        }
    }
    for(auto i : actListInterfaces)
        ui->listWidgetInter->addItem(i);
}
bool FormCurciut::checkHasInterfaces(QVector<PinNode::TYPE_INTERFACE> &vec, PinNode::TYPE_INTERFACE type)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == type)
        {
            return true;
        }
    }
    return false;
}
void FormCurciut::slotCut()
{
    QList<Node *> nodes;


    QList<QListWidgetItem*> listSys1      = ui->listWidgetSys1->selectedItems();
    QList<QListWidgetItem*> listSys2      = ui->listWidgetSys2->selectedItems();
    QList<QListWidgetItem*> listSysMiddle = ui->listWidgetSysMiddle->selectedItems();

    if(ui->checkBoxTransit->isChecked() == true)
    {

        domParser->loadTransitFile("/transform");

        Node *sys1;
        QList<Node *> listUnitSys2,listUnitTransit;
        for(auto i: domParser->listTransitFromFile)
        {
            listUnitSys2.clear();
            listUnitTransit.clear();
            sys1 = recFindNodeByIdName(domParser->rootItemData,i.nameSys1,Node::E_UNIT);
            if(sys1 == nullptr)
                domParser->outLog<<"Not Found sys"<<i.nameSys1<<"\n";
            for(auto j:i.nameTr)
            {
                listUnitTransit.append(recFindNodeByIdName(domParser->rootItemData,j,Node::E_UNIT));
            }
            for(auto j:i.namesSys2)
            {
                listUnitSys2.append(recFindNodeByIdName(domParser->rootItemData,j,Node::E_UNIT));
            }
            domParser->pasteUnitBetween(sys1,
                                        listUnitTransit,
                                        listUnitSys2,
                                        curInterfaces);
           domParser->updateCoords();

        }

        return;
    }
    if(ui->checkBoxUseFileTransform->isChecked() == true)
    {
        for(auto i:domParser->vecTransform)
        {
            curInterfaces.clear();
            nodes.clear();
            for(int j = 2;j < i.size();j++)
            {

                curInterfaces.append((PinNode::TYPE_INTERFACE)(i[j].toInt()));
            }
            Node *node = recFindNodeByName(domParser->rootItemData,i[1]);
            if(node != nullptr)
                 nodes.push_back(node);

            Node *selectNode = recFindNodeByName(domParser->rootItemData,i[0]);
            domParser->pasteUnitThrough(selectNode,nodes,curInterfaces);
        }
        return;
    }
    for(auto i:listSysMiddle)
    {

        Node *node = recFindNodeByName(domParser->rootItemData,i->text());
        if(node == nullptr)
            continue;
        nodes.push_back(node);
    }
    if((listSys1.isEmpty() == true) && (listSys2.isEmpty() == true))
    {
        QMessageBox msgBox;
        msgBox.setText("Not selected systems");
        msgBox.exec();
    }else if((listSys1.isEmpty() == true) || (listSys2.isEmpty() == true))
    {
        QString nameItem;

        if(listSys1.isEmpty() == false)
            nameItem = listSys1.first()->text();
        else
            nameItem = listSys2.first()->text();

        Node *selectNode = recFindNodeByName(domParser->rootItemData,nameItem);
        domParser->pasteUnitThrough(selectNode,nodes,curInterfaces);
        domParser->saveTransform(nameItem,nodes.first()->displayName,curInterfaces);
    }
    else
    {
        QList<Node *> listUnitSys2;
        for(auto i:listSys2)
        {
            listUnitSys2.append(recFindNodeByName(domParser->rootItemData,i->text()));
        }
        domParser->pasteUnitBetween(recFindNodeByName(domParser->rootItemData,ui->listWidgetSys1->currentItem()->text()),
                                    nodes,
                                    listUnitSys2,
                                    curInterfaces);
    }
}
void FormCurciut::recAddFindSystem(Node *root)
{
    if(root->type() == Node::E_UNIT)
    {
        UnitNode *unit = static_cast<UnitNode* > (root);
        ui->listWidgetSys1->addItem(root->displayName);
        ui->listWidgetSys2->addItem(root->displayName);
        if(unit->isTransit == true)
            ui->listWidgetSysMiddle->addItem(root->displayName);
    }
    for(auto i: root->child)
        recAddFindSystem(i);
}
Node* FormCurciut::recFindNodeByName(Node *root, QString str)
{
    if(root->displayName == str)
        return root;
    for(auto i:root->child)
    {
        Node* n = recFindNodeByName(i,str);
        if(n!=nullptr)
             return n;

    }
    return nullptr;
}
Node* FormCurciut::recFindNodeByIdName(Node *root, QString str,Node::Type t)
{
    if(root->idName == str && root->type() == t)
        return root;
    for(auto i:root->child)
    {
        Node* n = recFindNodeByIdName(i,str,t);
        if(n!=nullptr)
             return n;

    }
    return nullptr;
}
void FormCurciut::slotFormCurc(QString str)
{
    Node* node = recFindNodeByName(domParser->rootItemData,str);
    if(node != nullptr)
        domParser->saveForGraphvizForNode("select_" + node->displayName,node);
//    for(auto i:domParser->rootItemData->child[0]->child)
//    {
//        if(i->displayName == str)
//            domParser->saveForGraphvizForNode("selectNode",i);
//    }
}
void FormCurciut::slotPushGen()
{
    if(ui->listWidgetSys1->currentItem()->text() == ui->listWidgetSys2->currentItem()->text())
    {
        Node* node = recFindNodeByName(domParser->rootItemData,ui->listWidgetSys1->currentItem()->text());
        if(node != nullptr)
            domParser->saveForGraphvizForNode("select_" + node->displayName,node);

    }else
    { 
        Node* i1 = recFindNodeByName(domParser->rootItemData,ui->listWidgetSys1->currentItem()->text());
        if(i1 != nullptr)
                domParser->saveForGraphvizForNode("select_ "+i1->displayName,i1);

        Node* i2 = recFindNodeByName(domParser->rootItemData,ui->listWidgetSys2->currentItem()->text());
        if(i2 != nullptr)
                domParser->saveForGraphvizForNode("select_" + i2->displayName,i2);

        if(i1 != nullptr && i2 != nullptr)
            domParser->saveForGraphvizForNode("select_"+i1->displayName +"_"+ i2->displayName,i1,i2);
    }


}
//void FormCurciut::slotLoadTransitFile()
//{
//    domParser->loadTransitFile("/transform");
//}
void FormCurciut::slotDataBase()
{
    domParser->saveDataBase();

}
void FormCurciut::slotLoadData()
{
    DomParser::EPropertySaveToGV  type = DomParser::E_WIRES;
    if(ui->checkBoxCoord->isChecked() == true)
    {
        type = DomParser::E_CORDS;
    }
    if(ui->checkBoxInter->isChecked() == true)
    {
        type = DomParser::E_INTERFACES;
    }

    if(ui->checkBoxLoadParsed->isChecked() == true)
    {
        domParser->loadData("/parsed/base",type);
    }else if(ui->checkBoxLoad->isChecked() == true)
    {
        domParser->loadData("/curcuit",type);
    }
    if(domParser->rootItemData != nullptr)
        recAddFindSystem(domParser->rootItemData);

    domParser->loadDataPIC("/protocols");
}
void FormCurciut::slotExportRP()
{
    domParser->saveForRP();

}
FormCurciut::~FormCurciut()
{
    delete ui;
}
