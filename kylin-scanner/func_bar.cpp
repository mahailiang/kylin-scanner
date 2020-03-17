#include "func_bar.h"

FuncBar::FuncBar(QWidget *parent)
    : QWidget(parent)
{
    btnNorScan = new QPushButton(this);
    btnBeautify = new QPushButton(this);
    btnRectify = new QPushButton(this);
    btnOrc = new QPushButton(this);
    btnScan = new QPushButton(this);

    btnNorScan->setFixedSize(60,32);
    btnBeautify->setFixedSize(60,32);
    btnRectify->setFixedSize(60,32);
    btnOrc->setFixedSize(60,32);
    btnScan->setFixedSize(56,56);
    btnScan->setText("扫描");
    labNorScan = new QLabel(this);
    labBeautify = new QLabel(this);
    labRectify = new QLabel(this);
    labOrc = new QLabel(this);


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

    btnScan->setStyleSheet("QPushButton{background-color: rgb(232,160,73);border-radius:28px;color:rgb(232,232,232);}");
   // btnScan->setStyleSheet("color: rgb(232,232,232)");
   // btnScan->setStyleSheet("border-radius:28px");
    line1 = new QLabel();
    line1->setFrameStyle(QFrame::VLine);
    line1->setLineWidth(1);
    line1->setContentsMargins(0,0,0,0);
    line1->setStyleSheet("QLabel{color:rgb(32,30,29)}");

    line2 = new QLabel();
    line2->setFrameStyle(QFrame::VLine);
    line2->setLineWidth(1);
    line2->setContentsMargins(0,0,0,0);
    line2->setStyleSheet("QLabel{color:rgb(32,30,29)}");

    vBoxLay1 = new QVBoxLayout();
    vBoxLay2 = new QVBoxLayout();
    vBoxLay3 = new QVBoxLayout();
    vBoxLay4 = new QVBoxLayout();

    hBoxLay1 = new QHBoxLayout();
    hBoxLay2 = new QHBoxLayout();
    hBoxLay3 = new QHBoxLayout();
    hBoxLay4 = new QHBoxLayout();

    vBoxLay1->addWidget(btnNorScan);
    vBoxLay1->addWidget(labNorScan);
    vBoxLay1->setSpacing(10);

    vBoxLay2->addWidget(btnBeautify);
    vBoxLay2->addWidget(labBeautify);
    vBoxLay2->setSpacing(10);

    vBoxLay3->addWidget(btnRectify);
    vBoxLay3->addWidget(labRectify);
    vBoxLay3->setSpacing(10);

    vBoxLay4->addWidget(btnOrc);
    vBoxLay4->addWidget(labOrc);
    vBoxLay4->setSpacing(10);

    hBoxLay1->addStretch();
    hBoxLay1->addLayout(vBoxLay1);
    hBoxLay1->setContentsMargins(200,0,26,0);

    hBoxLay2->addLayout(vBoxLay2);
    hBoxLay2->addLayout(vBoxLay3);
    hBoxLay2->addLayout(vBoxLay4);
    hBoxLay2->setSpacing(26);
    hBoxLay2->setContentsMargins(26,0,30,0);

    hBoxLay3->addWidget(btnScan);
    hBoxLay3->setContentsMargins(30,0,200,0);
    hBoxLay3->addStretch();

    hBoxLay4->addLayout(hBoxLay1);
    hBoxLay4->addWidget(line1);
    hBoxLay4->addLayout(hBoxLay2);
    hBoxLay4->addWidget(line2);
    hBoxLay4->addLayout(hBoxLay3);
    setLayout(hBoxLay4);

}

FuncBar::~FuncBar()
{

}
