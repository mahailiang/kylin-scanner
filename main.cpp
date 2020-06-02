#include "widget.h"
#include <QApplication>
#include <QLabel>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    // For translator
    QTranslator translator;
    translator.load(QString("/home/yusq/back/zh_cn.qm"));

    a.installTranslator(&translator);
    */

    Widget w;

    w.show();


    return a.exec();
}
