
#include "./globalFunc/gl_func.h"

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

//    //! имя файла с настройками
//    nameMainFile="xml/setting.xml";
//    if(argc>1)
//        nameMainFile="xml/"+QString(argv[1]);

//    QPixmap pixmap(":/splash/intro");


    FormCurciut *formCurcuit = new FormCurciut;
    formCurcuit->show();
    app.setActiveWindow(formCurcuit);
//    //! создание заставки
//    QSplashScreen splash(pixmap);
//    splash.showMessage("Обновление БД ...", (Qt::AlignBottom)|(Qt::AlignLeft));
//    splash.show();
//    //! задание кодека
   // QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

    //QTextCodec * codec;
    //codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForTr(codec);
    //DomParser *domParser = new DomParser;
    //! задать активное окно
    //app.setActiveWindow(mppm);
    //! показать главную форму
    //mppm->show();
    //! закрыть заставку
    //splash.finish(mppm);
    //! запуск основного цикла обработки
    return app.exec();
}
