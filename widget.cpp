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
#include "widget.h"
#include <QVBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QSplitter>
#include <QLine>
#include <QFrame>
#include <QDebug>
#include <QBitmap>
#include "kylin_sane.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    KylinSane &instance = KylinSane::getInstance();
    instance.open_device();

    qDebug() << instance.getKylinSaneResolutions();

    pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);
    resize(860, 680);


    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(47, 44, 43));
    setAutoFillBackground(true);
    setPalette(pal);

    line =  new QFrame();
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(0, 32, 860, 1));
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("QLabel{color:rgb(32,30,29)}");


    pFuncBar = new  FuncBar();
    installEventFilter(pFuncBar);

    pScanSet = new ScanSet() ;
    installEventFilter(pScanSet);

    pScandisplay = new scan_display();
    installEventFilter(pScandisplay);
    if(instance.getKylinSaneStatus() == false)
        pScandisplay->set_no_device();
    pHboxLayout = new QHBoxLayout();
    pHboxLayout->setSpacing(0);
    pHboxLayout->addWidget(pScanSet);
    pHboxLayout->addWidget(pScandisplay);

    pLayout = new QVBoxLayout();
    pLayout->setSpacing(0);
    pLayout->addWidget(pTitleBar);
    pLayout->addWidget(line);
    pLayout->addWidget(pFuncBar);
    pLayout->addLayout(pHboxLayout);
    pLayout->setContentsMargins(0, 0, 0, 0);


    setLayout(pLayout);
    connect(pScanSet,&ScanSet::save_image_signal,this,&Widget::save_image);
    connect(pFuncBar,&FuncBar::send_Orc_Begin,pScandisplay,&scan_display::orc);
    connect(pFuncBar,&FuncBar::send_Orc_End,pScandisplay,&scan_display::orc);
    connect(pFuncBar,&FuncBar::send_Orc_Begin,pScanSet,&ScanSet::modify_save_button);
    connect(pFuncBar,&FuncBar::send_Orc_End,pScanSet,&ScanSet::modify_save_button);
    connect(pFuncBar,&FuncBar::send_Scan_End,pScandisplay,&scan_display::scan);
    connect(pFuncBar,&FuncBar::send_Scan_End,this,&Widget::save_scan_file);
    connect(pFuncBar,&FuncBar::send_Rectify_Begin,pScandisplay,&scan_display::rectify);
    connect(pFuncBar, &FuncBar::send_Beauty_Begin, pScandisplay, &scan_display::beauty);
    connect(pFuncBar, &FuncBar::send_Beauty_End, pScandisplay, &scan_display::beauty);
}

Widget::~Widget()
{

}
int toUnicode(QString str)
{
    char*  ch;
    QByteArray ba = str.toLatin1();
    ch=ba.data();
    return ch[0] + (ch[1] ? toUnicode(ch + 1) : 0);
}

constexpr inline int U(const char* str)
{
    return str[0] + (str[1] ? U(str + 1) : 0);
}

void Widget::set_pdf_size(QPdfWriter *pdfWriter, QString size)
{
    switch (toUnicode(size))
    {
    case U("A0"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A0));
        break;
    case U("A1"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A1));
        break;
    case U("A2"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A2));
        break;
    case U("A3"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A3));
        break;
    case U("A4"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A4));
        break;
    case U("A5"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A5));
        break;
    case U("A6"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A6));
        break;
    case U("A7"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A7));
        break;
    case U("A8"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A8));
        break;
    case U("A9"):
        pdfWriter->setPageSize(QPageSize(QPageSize::A9));
        break;
    default:
        pdfWriter->setPageSize(QPageSize(QPageSize::A4));
        break;
    }
}

void Widget::save_to_pdf(QImage img, QString pathName)
{

    QFile pdfFile(pathName);
    pdfFile.open(QIODevice::WriteOnly);
    QPdfWriter *pdfWriter = new QPdfWriter(&pdfFile);
    set_pdf_size(pdfWriter,pScanSet->getTextSize());
    int resolution = pScanSet->getTextResalution().toInt();
    pdfWriter->setResolution(resolution);//像素

    int pageMargin = 0;
    pdfWriter->setPageMargins(QMarginsF(pageMargin, pageMargin, pageMargin, pageMargin));

    QPainter *pdfPainter = new QPainter(pdfWriter);

    int yCurrentP = 0;
    int xCurrentP = 0;


//    std::string titleImageFileName = "/tmp/scanner/scan.png";
    QString titleImageFileName = "/tmp/scanner/scan.png";
    QPixmap titleImage;
//    titleImage.load(QString::fromStdString(titleImageFileName));
    titleImage.load(titleImageFileName);
    QPixmap pixmap = QPixmap::fromImage(img);
    pdfPainter->drawPixmap(xCurrentP, yCurrentP, pixmap.width(), pixmap.height(), pixmap);

    delete pdfPainter;
    delete pdfWriter;
    pdfFile.close();
}

void Widget::save_image(QString fileName)
{
    QImage *img = NULL;
    img = pScandisplay->imageSave(fileName);
    if(img)
        save_to_pdf(*img,fileName);
}

void Widget::save_scan_file()
{
    QImage img;
    img.load("/tmp/scanner/scan.pnm");
    QString pathName = pScanSet->getTextLocation() + "/" + pScanSet->getTextName();
    qDebug()<<"pathName:"<<pathName;
    QString format = pScanSet->getTextFormat();
    if((format == "jpg") || (format == "png") || (format == "bmp"))
    {
        QString newformat = "." + format;
        qDebug()<<"newformat:"<<newformat;
        if(pathName.endsWith(newformat,Qt::CaseSensitive))
        {
            img.save(pathName);
        }
        else
        {
            pathName += newformat;
            qDebug()<<"pathName:"<<pathName;
            img.save(pathName);
        }
    }
    else if(format == "pdf")
    {
        QString newformat = "." + format;
        qDebug()<<"newformat:"<<newformat;
        if(!pathName.endsWith(newformat,Qt::CaseSensitive))
        {
            pathName += newformat;
            qDebug()<<"pathName:"<<pathName;
        }
        save_to_pdf(img,pathName);
    }
}



