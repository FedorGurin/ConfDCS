#ifndef FORMCURCIUT_H
#define FORMCURCIUT_H

#include <QWidget>
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
     bool checkHasInterfaces(QVector<PinNode::TYPE_INTERFACE> &vec, PinNode::TYPE_INTERFACE type);
     DomParser *domParser;
private:
    Ui::FormCurciut *ui;
public slots:
    void slotFormCurc(QString string);
    void slotPushGen();
    void slotDataBase();
    void slotLoadData();
    void slotCut();
    void slotItemSelection();
};

#endif // FORMCURCIUT_H
