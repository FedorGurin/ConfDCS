#ifndef FORMCURCIUT_H
#define FORMCURCIUT_H

#include <QWidget>
#include "DomParser.h"

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
     DomParser *domParser;
private:
    Ui::FormCurciut *ui;
public slots:
    void slotFormCurc(QString string);
    void slotPushGen();
    void slotDataBase();
    void slotLoadData();
};

#endif // FORMCURCIUT_H
