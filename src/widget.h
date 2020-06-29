/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
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
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPdfWriter>
#include <QPainter>
#include "scan_display.h"
#include <scan_set.h>
#include "title_bar.h"
#include "func_bar.h"
class Widget : public QWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = 0);
    ~Widget();
    void set_pdf_size(QPdfWriter *pdfWriter,QString size);
    void save_to_pdf(QImage img, QString pathName);

private:
    TitleBar *pTitleBar;
    QFrame *line;
    FuncBar *pFuncBar;
    ScanSet *pScanSet;
    scan_display *pScandisplay;
    QHBoxLayout *pHboxLayout;
    QVBoxLayout *pLayout;
    KylinSane& instance = KylinSane::getInstance();

private slots:
    void save_image(QString fileName);
    void save_scan_file();



};

#endif // WIDGET_H
