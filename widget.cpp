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
}

Widget::~Widget()
{

}

void Widget::save_image(QString fileName)
{
    pScandisplay->imageSave(fileName);
}


