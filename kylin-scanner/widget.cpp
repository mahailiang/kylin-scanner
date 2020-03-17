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


    QLabel * line1 = new QLabel();
    line1->setFrameStyle(QFrame::HLine| QFrame::Plain);// | QFrame::Raised
    line1->setLineWidth(0);
    line1->setMidLineWidth(1);
    line1->setStyleSheet("QLabel{color:rgb(32,30,29)}");

    QLabel * line2 = new QLabel();
    line2->setFrameStyle(QFrame::HLine| QFrame::Sunken);// | QFrame::Raised
    line2->setLineWidth(0);
    line2->setMidLineWidth(1);
    line2->setStyleSheet("QLabel{color:rgb(32,30,29)}");



    FuncBar *pFuncBar = new  FuncBar();
    installEventFilter(pFuncBar);

    ScanSet *pScanSet = new ScanSet() ;
    installEventFilter(pScanSet);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->setSpacing(0);
    pLayout->addWidget(line1);
    pLayout->setSpacing(0);
    pLayout->addWidget(pFuncBar);
    pLayout->setSpacing(0);
    pLayout->addWidget(line2);
    pLayout->setSpacing(0);
    pLayout->addWidget(pScanSet);
    pLayout->setSpacing(0);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 5, 0, 0);



    setLayout(pLayout);
}

Widget::~Widget()
{

}
