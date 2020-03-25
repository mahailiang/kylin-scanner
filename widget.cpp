#include "widget.h"
#include "title_bar.h"
#include "func_bar.h"
#include <scan_set.h>
#include <QVBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QSplitter>
#include <QLine>
#include <QFrame>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    TitleBar *pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);
    resize(860, 680);
//    setWindowTitle("Custom Window");
//    setWindowIcon(QIcon(":/icon/icon/close.png"));

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(47, 44, 43));
    setAutoFillBackground(true);
    setPalette(pal);

    line =  new QFrame();
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(0, 32, 860, 1));
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("QLabel{color:rgb(32,30,29)}");


    FuncBar *pFuncBar = new  FuncBar();
    installEventFilter(pFuncBar);

    ScanSet *pScanSet = new ScanSet() ;
    installEventFilter(pScanSet);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->setSpacing(0);
    pLayout->addWidget(pTitleBar);
    pLayout->addWidget(line);
    pLayout->addWidget(pFuncBar);
    pLayout->addWidget(pScanSet);
//    pLayout->addStretch();
    pLayout->setContentsMargins(0, 0, 0, 0);



    setLayout(pLayout);
}

Widget::~Widget()
{

}
