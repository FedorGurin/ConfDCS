#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QSplashScreen>
#include <QResource>
#include "formCurciut.h"

int main(int argc,char *argv[])
{

    QApplication app(argc,argv);
    app.setQuitOnLastWindowClosed(true);

    FormCurciut *formCurcuit = new FormCurciut;
    formCurcuit->show();
    app.setActiveWindow(formCurcuit);

    return app.exec();
}
