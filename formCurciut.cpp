#include "formCurciut.h"
#include "ui_formCurciut.h"
#include "UnitNode.h"
#include <QMessageBox>
FormCurciut::FormCurciut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCurciut)
{
    ui->setupUi(this);
    domParser = new DomParser;


    /*for(auto i:domParser->rootItemData->child[0]->child)
    {
        ui->listWidgetSys1->addItem(i->displayName);
        ui->listWidgetSys2->addItem(i->displayName);
    }*/
    connect(ui->pushButton,         SIGNAL(clicked()),this,SLOT(slotPushGen()));
    connect(ui->pushButtonDataBase, SIGNAL(clicked()),this,SLOT(slotDataBase()));
    connect(ui->pushButtonLoad,     SIGNAL(clicked()),this,SLOT(slotLoadData()));
    connect(ui->pushButtonCut,      SIGNAL(clicked()),this,SLOT(slotCut()));
}
void FormCurciut::slotCut()
{
    QList<Node *> nodes;

    QList<QListWidgetItem*> items = ui->listWidgetSysMiddle->selectedItems();

    for(auto i:items)
    {

        Node *node = recFindNodeByName(domParser->rootItemData,i->text());
        if(node == nullptr)
            continue;
        nodes.push_back(node);
    }
    if(ui->listWidgetSys1->currentItem() == nullptr || ui->listWidgetSys2->currentItem() == nullptr)
    {
        QMessageBox msgBox;
        msgBox.setText("Not selected systems");
        msgBox.exec();

    }else
    {
        domParser->pasteUnitBetween(recFindNodeByName(domParser->rootItemData,ui->listWidgetSys1->currentItem()->text()),
                                    nodes,
                                    recFindNodeByName(domParser->rootItemData,ui->listWidgetSys2->currentItem()->text()));
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
    if(domParser->rootItemData != 0)
        recAddFindSystem(domParser->rootItemData);

    domParser->loadDataPIC("/protocols");
}
FormCurciut::~FormCurciut()
{
    delete ui;
}
