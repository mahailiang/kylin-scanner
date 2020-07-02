/*
* Copyright (C) 2020 KYLIN SOFTWARE Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
#include "widget.h"
#include <QApplication>
#include <QLabel>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // For translations with different language environments
    QTranslator translator;
    QString locale = "/usr/share/kylin-scanner/translations/kylin-scanner." + QLocale::system().name();
    qDebug() << locale ;

    translator.load(locale);
    a.installTranslator(&translator);

    /*
    QTranslator qtTranslator;
    QString dir = a.applicationDirPath() + "/" + "translations";

    if (qtTranslator.load(QLocale(), "language", ".", dir, ".qm"))
    {
        a.installTranslator(&qtTranslator);
    }
    */

    Widget w;

    w.show();


    return a.exec();
}
