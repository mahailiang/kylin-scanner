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
#ifndef FUNC_BAR_H
#define FUNC_BAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QInputEvent>

#include "kylin_sane.h"
#include "embelish.h"

class FuncBar : public QWidget
{
    Q_OBJECT

public:
    explicit FuncBar(QWidget *parent = nullptr);
    ~FuncBar();
    void keyPressEvent(QKeyEvent *e);
    int n = 0;
    int flagBeauty = 0; //一键美化标志


private:
    QPushButton *btnNorScan ;
    QPushButton *btnBeautify;
    QPushButton *btnRectify;
    QPushButton *btnOrc;
    QPushButton *btnScan;
    QLabel *labNorScan;
    QLabel *labBeautify;
    QLabel *labRectify;
    QLabel *labOrc;
    QFrame *line1;
    QFrame *line2;
    QVBoxLayout *vBoxLay1;
    QVBoxLayout *vBoxLay2;
    QVBoxLayout *vBoxLay3;
    QVBoxLayout *vBoxLay4;
    QHBoxLayout *hBoxLay1;
    QHBoxLayout *hBoxLay2;
    QHBoxLayout *hBoxLay3;
    QHBoxLayout *hBoxLay4;

private slots:
    void on_btnOrc_clicked();
    void on_btnScan_clicked();
    void on_btnRectify_clicked();
    void on_btnBeauty_clicked();

Q_SIGNALS:
    void send_Orc_Begin();
    void send_Orc_End();
    void send_Scan_End();
    void send_Rectify_Begin();
    void send_Beauty_Begin();
    void send_Beauty_End();

};
#endif // FUNC_BAR_H
