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
#include "func_bar.h"

FuncBar::FuncBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(80);
    btnNorScan = new QPushButton();
    btnBeautify = new QPushButton();
    btnRectify = new QPushButton();
    btnOrc = new QPushButton();
    btnScan = new QPushButton();

    btnNorScan->setFixedSize(60,32);
    btnBeautify->setFixedSize(60,32);
    btnRectify->setFixedSize(60,32);
    btnOrc->setFixedSize(60,32);
    btnScan->setFixedSize(56,56);
    btnScan->setText("扫描");
    labNorScan = new QLabel();
    labBeautify = new QLabel();
    labRectify = new QLabel();
    labOrc = new QLabel();


    labNorScan->setText("普通扫描");
    labNorScan->setAlignment(Qt::AlignCenter);
    labNorScan->setStyleSheet("color:rgb(232,232,232)");
    labNorScan->setFixedSize(56,16);

    labBeautify->setText("一键美化");
    labBeautify->setAlignment(Qt::AlignCenter);
    labBeautify->setStyleSheet("color:rgb(232,232,232)");
    labBeautify->setFixedSize(56,16);

    labRectify->setText("智能纠偏");
    labRectify->setAlignment(Qt::AlignCenter);
    labRectify->setStyleSheet("color:rgb(232,232,232)");
    labRectify->setFixedSize(56,16);

    labOrc->setText("文字识别");
    labOrc->setAlignment(Qt::AlignCenter);
    labOrc->setStyleSheet("color:rgb(232,232,232)");
    labOrc->setFixedSize(56,16);


    btnNorScan->setStyleSheet("QPushButton{image: url(:/icon/icon/norscan.png);border:none;background-color:rgb(15,08,01);border-radius:6px;}"
                              "QPushButton:hover{image: url(:/icon/icon/norscan.png);border:none;background-color:rgb(39,208,127);border-radius:6px;}"
                                "QPushButton:checked{image: url(:/icon/icon/norscan.png);border:none;background-color:rgb(39,208,127);border-radius:6px;}");
    btnBeautify->setStyleSheet("QPushButton{image: url(:/icon/icon/beautify.png);border:none;background-color:rgb(15,08,01);border-radius:6px;}"
                              "QPushButton:hover{image: url(:/icon/icon/beautify.png);border:none;background-color:rgb(39,208,127);border-radius:6px;}"
                                "QPushButton:checked{image: url(:/icon/icon/beautify.png);border:none;background-color:rgb(39,208,127);border-radius:6px;}");
    btnRectify->setStyleSheet("QPushButton{image: url(:/icon/icon/rectify.png);border:none;background-color:rgb(15,08,01);border-radius:6px;}"
                              "QPushButton:hover{image: url(:/icon/icon/rectify.png);border:none;background-color:rgb(39,208,127);border-radius:6px;}"
                                "QPushButton:checked{image: url(:/icon/icon/rectify.png);border:none;background-color:rgb(39,208,127);border-radius:6px;}");
    btnOrc->setStyleSheet("QPushButton{image: url(:/icon/icon/orc.png);border:none;background-color:rgb(15,08,01);border-radius:6px;}"
                              "QPushButton:hover{image: url(:/icon/icon/orc.png);border:none;background-color:rgb(39,208,127);border-radius:6px;}"
                                "QPushButton:checked{image: url(:/icon/icon/orc.png);border:none;background-color:rgb(39,208,127);border-radius:6px;}");
//    btnScan->setStyleSheet("QPushButton{background-color:rgb(232,,160,73);border-radius:28px;}"
//                              "QPushButton:hover{image: url(:/icon/icon/scanner.gif);border:none;background-color:rgb(39,208,127);border-radius:28px;}"
//                                "QPushButton:checked{image: url(:/icon/icon/scanner.gif);border:none;background-color:rgb(39,208,127);border-radius:28px;}");

    btnScan->setStyleSheet("QPushButton{background-color: rgb(232,160,73);border-radius:28px;color:rgb(232,232,232);}"
                           "QPushButton:hover{image: url(:/icon/icon/scanner.gif);border-radius:28px;}");
    line1 = new QFrame();
    line1->setObjectName(QString::fromUtf8("line1"));
    line1->setMaximumWidth(1);
    line1->setMaximumHeight(48);
    line1->setMinimumHeight(48);
    line1->setFrameShape(QFrame::VLine);
    line1->setStyleSheet("QLabel{color:rgb(32,30,29)}");

    line2 = new QFrame();
    line2->setObjectName(QString::fromUtf8("line2"));
    line2->setMaximumWidth(1);
    line2->setMaximumHeight(48);
    line2->setMinimumHeight(48);
    line2->setFrameStyle(QFrame::VLine);
    line2->setStyleSheet("QLabel{color:rgb(32,30,29)}");

    vBoxLay1 = new QVBoxLayout();
    vBoxLay2 = new QVBoxLayout();
    vBoxLay3 = new QVBoxLayout();
    vBoxLay4 = new QVBoxLayout();

    hBoxLay1 = new QHBoxLayout();
    hBoxLay2 = new QHBoxLayout();
    hBoxLay3 = new QHBoxLayout();
    hBoxLay4 = new QHBoxLayout();

    // 先隐藏
    btnNorScan->hide();
    labNorScan->hide();
    /*
    vBoxLay1->setSpacing(0);
    vBoxLay1->addSpacing(2);
    vBoxLay1->addWidget(btnNorScan);
    vBoxLay1->addSpacing(10);
    vBoxLay1->addWidget(labNorScan);
   // vBoxLay1->addSpacing(10);
   */

    vBoxLay2->setSpacing(0);
    vBoxLay2->addSpacing(2);
    vBoxLay2->addWidget(btnBeautify);
    vBoxLay2->addSpacing(10);
    vBoxLay2->addWidget(labBeautify);
  //  vBoxLay2->addSpacing(10);


    vBoxLay3->setSpacing(0);
    vBoxLay3->addSpacing(2);
    vBoxLay3->addWidget(btnRectify);
    vBoxLay3->addSpacing(10);
    vBoxLay3->addWidget(labRectify);


    vBoxLay4->setSpacing(0);
    vBoxLay4->addSpacing(2);
    vBoxLay4->addWidget(btnOrc);
    vBoxLay4->addSpacing(10);
    vBoxLay4->addWidget(labOrc);


    hBoxLay1->setSpacing(0);
    hBoxLay1->addStretch();
    hBoxLay1->addLayout(vBoxLay1);
    hBoxLay1->setContentsMargins(189,0,26,0);

    hBoxLay2->setSpacing(0);
    hBoxLay2->addLayout(vBoxLay2);
    hBoxLay2->addSpacing(26);
    hBoxLay2->addLayout(vBoxLay3);
    hBoxLay2->addSpacing(26);
    hBoxLay2->addLayout(vBoxLay4);    
    hBoxLay2->setContentsMargins(26,0,30,0);

    hBoxLay3->setSpacing(0);
    hBoxLay3->addWidget(btnScan);
    hBoxLay3->setContentsMargins(30,0,189,0);
    hBoxLay3->addStretch();

    hBoxLay4->setSpacing(0);
    hBoxLay4->addLayout(hBoxLay1);
    hBoxLay4->addWidget(line1);
    hBoxLay4->addLayout(hBoxLay2);
    hBoxLay4->addWidget(line2);
    hBoxLay4->addLayout(hBoxLay3);
    setLayout(hBoxLay4);

    connect(btnOrc,SIGNAL(clicked()),this,SLOT(on_btnOrc_clicked()));
    connect(btnScan, SIGNAL(clicked()), this, SLOT(on_btnScan_clicked()));
    connect(btnRectify, SIGNAL(clicked()), this, SLOT(on_btnRectify_clicked()));
}

FuncBar::~FuncBar()
{

}

void FuncBar::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Z && e->modifiers() ==  Qt::ControlModifier)
    {
        if(n == 1)
        {
            n = 0;
            emit send_Orc_End();
        }
    }
}
//QString orc_text;
void FuncBar::on_btnOrc_clicked()
{
    if(n == 0)
    {
        n = 1;
        emit send_Orc_Begin();
    }
    else
    {
        n = 0;
        emit send_Orc_End();
    }

}

void FuncBar::on_btnScan_clicked()
{
    KylinSane& instance = KylinSane::getInstance();
    if(instance.getKylinSaneStatus() == true)
    {
        instance.start_scanning(instance.userInfo);
        qDebug()<<"start_scanning end!!!";
        emit send_Scan_End();
    }
}
void FuncBar::on_btnRectify_clicked()
{
    qDebug()<<"send_Rectify_Begin"<<endl;
    emit send_Rectify_Begin();
}
