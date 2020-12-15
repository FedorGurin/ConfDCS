#ifndef FORMCURCIUT_H
#define FORMCURCIUT_H

#include <QWidget>
#include <QListWidgetItem>
#include "DomParser.h"
#include "pinNode.h"
namespace Ui {
class FormCurciut;
}

class FormCurciut : public QWidget
{
    Q_OBJECT

public:
    explicit FormCurciut(QWidget *parent = nullptr);
    ~FormCurciut();
     void recAddFindSystem(Node *root);
     Node* recFindNodeByName(Node *root, QString str);
     Node* recFindNodeByIdName(Node *root, QString str,Node::Type t);
     bool checkHasInterfaces(QVector<PinNode::TYPE_INTERFACE> &vec, PinNode::TYPE_INTERFACE type);
     DomParser *domParser;
private:
    Ui::FormCurciut *ui;
    //! список выбраннхы интерфейсов
    QVector<QListWidgetItem *> actListInterfaces;
    QVector<PinNode::TYPE_INTERFACE> curInterfaces;
public slots:
    void slotFormCurc(QString string);
    void slotPushGen();
    void slotDataBase();
    void slotLoadData();
    void slotExportRP();
    //! генерация жгутов
    void slotGenRoute();
    //! функция врезки данных
    void slotCut();
    void slotItemSelection();
    void slotItemSelectionInterfaces();
};

#endif // FORMCURCIUT_H
