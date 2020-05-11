#include "scan_display.h"
#include "func_bar.h"
#include <QDebug>
#include <QToolTip>
#include <QTextEdit>
scan_display::scan_display(QWidget *parent)
    : QWidget(parent)
{

    labDisplay1 = new QLabel();
    labDisplay2 = new QLabel();
    labDisplay3 = new QLabel();
    labDisplay4 = new QLabel();
    labDisplay5 = new QLabel();
    labDisplay6 = new QLabel();
    labDisplay7 = new QLabel();

    btnTool = new QPushButton();
    btnTool1 = new QPushButton();


    myWidget = new QWidget();
    myWidget1 = new QWidget();
    myWidget2 = new QWidget();

    img = new QImage();
    img1 = new QImage();
    img2 = new QImage();
    img4 = new QImage();
    img5 = new QImage();
    vBoxScanSet = new QVBoxLayout();
    vBoxScanSet1 = new QVBoxLayout(this);
    vBoxScanSet2 = new QVBoxLayout();
    hBoxScanSet = new QHBoxLayout();
    hBoxScanSet1 = new QHBoxLayout();

    vStackedLayout = new QStackedLayout();

    labDisplay2->setParent(myWidget);
    labDisplay3->setParent(myWidget);
    labDisplay1->setMinimumSize(600,567);
    labDisplay2->setMinimumSize(600,320);
    labDisplay3->setMinimumSize(600,231);
    labDisplay4->setMinimumSize(600,567);
    labDisplay5->setMinimumSize(560,567);
    labDisplay6->setFixedWidth(40);
    labDisplay7->setMinimumSize(560,567);


    labDisplay1->setText(" ");


    img->load(":/icon/icon/connect_device.png");
    labDisplay2->setPixmap(QPixmap::fromImage(*img));
    labDisplay2->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);

    img1->load(":/icon/icon/a.png");
    labDisplay4->setPixmap(QPixmap::fromImage(*img1));
    labDisplay4->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPointSize(24);
    labDisplay3->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(232,232,232));
    labDisplay3->setPalette(pa);
    labDisplay3->setText("请先连接扫描仪！");
    labDisplay3->setAlignment(Qt::AlignHCenter|Qt::AlignTop);



    vBoxScanSet->setSpacing(0);
    vBoxScanSet->addStretch();
    vBoxScanSet->addWidget(labDisplay2);
    vBoxScanSet->addSpacing(16);
    vBoxScanSet->addWidget(labDisplay3);
    vBoxScanSet->addStretch();
    vBoxScanSet->setContentsMargins(0,0,0,0);
    myWidget->setLayout(vBoxScanSet);

    labDisplay5->setParent(myWidget1);
    labDisplay6->setParent(myWidget1);
    btnTool->setParent(myWidget1);
    btnTool->setFixedSize(12,30);
    btnTool->setStyleSheet("QPushButton{border-image: url(:/icon/icon/toolbutton.png);border:none;background-color:#0f0801;border-radius:0px;}");
    img5->load(":/icon/icon/a.png");
    labDisplay5->setPixmap(QPixmap::fromImage(*img5));
    labDisplay5->setAlignment(Qt::AlignCenter);
    labDisplay6->setStyleSheet("QLabel{background-color:#0f0801;}");

    hBoxScanSet->setSpacing(0);
    hBoxScanSet->addSpacing(2);
    hBoxScanSet->addStretch();
    hBoxScanSet->addWidget(labDisplay5);
//    hBoxScanSet->addSpacing(65);
    hBoxScanSet->addStretch();
    hBoxScanSet->addSpacing(2);
    hBoxScanSet->addWidget(labDisplay6);
    hBoxScanSet->addSpacing(2);
    hBoxScanSet->addWidget(btnTool);
    hBoxScanSet->setContentsMargins(0,0,4,0);
    myWidget1->setLayout(hBoxScanSet);


    editlayout = new edit_bar();
    labDisplay7->setParent(myWidget2);
    btnTool1->setParent(myWidget2);
    editlayout->setParent(myWidget2);

    img2->load(":/icon/icon/a.png");
    labDisplay7->setPixmap(QPixmap::fromImage(*img2));
    labDisplay7->setAlignment(Qt::AlignCenter);


    btnTool1->setFixedSize(12,30);
    btnTool1->setStyleSheet("QPushButton{border-image: url(:/icon/icon/toolbutton1.png);border:none;background-color:#0f0801;border-radius:0px;}");

    hBoxScanSet1->setSpacing(0);
    hBoxScanSet1->addSpacing(2);
    hBoxScanSet1->addStretch();
    hBoxScanSet1->addWidget(labDisplay7);
//    hBoxScanSet1->addSpacing(65);
    hBoxScanSet1->addStretch();
    hBoxScanSet1->addSpacing(2);
    hBoxScanSet1->addWidget(editlayout);
    hBoxScanSet1->addSpacing(2);
    hBoxScanSet1->addWidget(btnTool1);
    hBoxScanSet1->setContentsMargins(0,0,4,0);
    myWidget2->setLayout(hBoxScanSet1);


    vStackedLayout->addWidget(myWidget1);
    vStackedLayout->addWidget(myWidget2);
    vStackedLayout->addWidget(myWidget);
    vStackedLayout->addWidget(labDisplay1);
    vStackedLayout->addWidget(labDisplay4);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(15, 8, 1));
    setAutoFillBackground(true);
    setPalette(pal);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    vBoxScanSet1->setSpacing(0);
    vBoxScanSet1->addLayout(vStackedLayout);
    vBoxScanSet1->setContentsMargins(0,0,0,0);
    setLayout(vBoxScanSet1);
    connect(btnTool,SIGNAL(clicked()),this,SLOT(switchPage()));
    connect(btnTool1,SIGNAL(clicked()),this,SLOT(switchPage()));
    connect(editlayout->btnRotate,SIGNAL(clicked()),this,SLOT(rotating()));
    connect(editlayout->btnTailor,SIGNAL(clicked()),this,SLOT(switchPage1()));
    connect(editlayout->btnSymmetry,SIGNAL(clicked()),this,SLOT(symmetry()));
    connect(editlayout->btnWatermark,SIGNAL(clicked()),this,SLOT(addmark()));
}

void scan_display::keyPressEvent(QKeyEvent *e)
{
    if (((e->key() == Qt::Key_Return) || (e->key() == 0x20)) && (vStackedLayout->currentWidget() == myWidget3))
    {
        QImage newimage;
        int x = 0, y = 0;
        x = labDisplay8->getX1() - ((labDisplay8->width() - img2->width()) / 2);
        y = labDisplay8->getY1() - ((labDisplay8->height() - img2->height()) / 2);

        newimage = img2->copy(x,y,labDisplay8->getX2()-labDisplay8->getX1(),labDisplay8->getY2()-labDisplay8->getY1());
        *img2 = newimage;
        labDisplay7->setPixmap(QPixmap::fromImage(*img2));
        vStackedLayout->setCurrentIndex(index);
        vStackedLayout->removeWidget(myWidget3);

    }
    if(e->key() == Qt::Key_Z && e->modifiers() ==  Qt::ControlModifier)
    {

//        *img2 = img4->copy();
        if(!stack.isEmpty())
        {
            *img2 = stack.pop();
            labDisplay7->setPixmap(QPixmap::fromImage(*img2));
            vStackedLayout->setCurrentIndex(index);
        }
    }
}

void scan_display::rotating()
{

    QMatrix matrix;
    *img4 = img2->copy();
    stack.push(*img4);
    matrix.rotate(270);
    *img2 = img2->transformed(matrix);
    labDisplay7->setPixmap(QPixmap::fromImage(*img2));

}

void scan_display::symmetry()
{
    *img4 = img2->copy();
    stack.push(*img4);
    *img2=img2->mirrored(true,false);
    labDisplay7->setPixmap(QPixmap::fromImage(*img2));
}

void scan_display::addmark()
{

    if(n == 0)
    {
        n = 1;
        img6 = new QImage();
        *img6 = img2->copy();
    }
    QString text;
    mark_dialog *dialog = new mark_dialog(this);
    int ret=dialog->exec();// 以模态方式显示对话框，用户关闭对话框时返回 DialogCode值
    if (ret==QDialog::Accepted) //OK键被按下,对话框关闭，若设置了setAttribute(Qt::WA_DeleteOnClose)，对话框被释放，无法获得返回值
    { //OK键被按下，获取对话框上的输入，设置行数和列数
        text = dialog->get_lineedit();
        *img4 = img2->copy();
        stack.push(*img4);
        *img2 = img6->copy();
        QPainter painter(img2);
        int fontSize = 25, spacing = 10;
        QFont font("微软雅黑", fontSize, QFont::Thin);
        font.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
        painter.setFont(font);
        painter.setPen(QColor(150, 150, 150));
        painter.translate(img2->width() / 2, -img2->width() / 2);//调整位置
        painter.rotate(15);

        int squareEdgeSize = img2->width() * sin(45) + img2->height() * sin(45);//对角线长度
        int hCount = squareEdgeSize / ((fontSize + spacing) * (text.size() + 1)) + 1;
        int x = squareEdgeSize / hCount + (fontSize + spacing) * 3;
        int y = x / 2;

        for (int i = 0; i < hCount; i++)
        {
            for (int j = 0; j < hCount * 2; j++)
            {
               painter.drawText(x * i, y * j,text);
            }
        }
        labDisplay7->setPixmap(QPixmap::fromImage(*img2));
    }
    delete dialog; //删除对话框

}



void scan_display::switchPage()
{
    index++;
    if(index > 1)
        index = 0;
    vStackedLayout->setCurrentIndex(index);
}

void scan_display::switchPage1()
{
    btnTool2 = new QPushButton();
    labDisplay8 = new my_label();
    editlayout1 = new edit_bar();
    myWidget3 = new QWidget();
    hBoxScanSet2 = new QHBoxLayout();
    img3 = new QImage();
    labDisplay8->setMinimumSize(560,567);
    labDisplay8->setParent(myWidget3);
    btnTool2->setParent(myWidget3);
    editlayout1->setParent(myWidget3);
    *img3 = img2->copy();
    *img4 = img2->copy();
    stack.push(*img4);
    labDisplay8->setPixmap(QPixmap::fromImage(*img3));
    labDisplay8->setAlignment(Qt::AlignCenter);

    btnTool2->setFixedSize(12,30);
    btnTool2->setStyleSheet("QPushButton{border-image: url(:/icon/icon/toolbutton1.png);border:none;background-color:#0f0801;border-radius:0px;}");

    hBoxScanSet2->setSpacing(0);
    hBoxScanSet2->addSpacing(2);
    hBoxScanSet2->addStretch();
    hBoxScanSet2->addWidget(labDisplay8);
//    hBoxScanSet2->addSpacing(65);
    hBoxScanSet2->addStretch();
    hBoxScanSet2->addSpacing(2);
    hBoxScanSet2->addWidget(editlayout1);
    hBoxScanSet2->addSpacing(2);
    hBoxScanSet2->addWidget(btnTool2);
    hBoxScanSet2->setContentsMargins(0,0,4,0);
    myWidget3->setLayout(hBoxScanSet2);
    vStackedLayout->addWidget(myWidget3);
    vStackedLayout->setCurrentWidget(myWidget3);
}

edit_bar::edit_bar(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(40,220);
    vBoxEditBar = new QVBoxLayout(this);
    btnRotate = new QPushButton();
    btnTailor = new QPushButton();
    btnSymmetry = new QPushButton();
    btnWatermark = new QPushButton();

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(232, 232, 232));
    setAutoFillBackground(true);
    setPalette(pal);

    btnRotate->setFixedSize(30,30);
    btnTailor->setFixedSize(30,30);
    btnSymmetry->setFixedSize(30,30);
    btnWatermark->setFixedSize(30,30);
    btnRotate->setToolTip("旋转");
  //  btnTailor->setToolTip("裁剪");

    btnRotate->setStyleSheet("QPushButton{border-image: url(:/icon/icon/rotate.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}"
                              "QPushButton:hover{border-image: url(:/icon/icon/rotate-click.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/rotate-click.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}");
    btnTailor->setStyleSheet("QPushButton{border-image: url(:/icon/icon/tailor.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}"
                              "QPushButton:hover{border-image: url(:/icon/icon/tailor-click.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/tailor-click.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}");
    btnSymmetry->setStyleSheet("QPushButton{border-image: url(:/icon/icon/symmetry.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}"
                              "QPushButton:hover{border-image: url(:/icon/icon/symmetry-click.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/symmetry-click.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}");
    btnWatermark->setStyleSheet("QPushButton{border-image: url(:/icon/icon/watermark.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}"
                              "QPushButton:hover{border-image: url(:/icon/icon/watermark-click.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}"
                                "QPushButton:checked{border-image: url(:/icon/icon/watermark-click.png);border:none;background-color:rgb(232,232,232);border-radius:0px;}");
    vBoxEditBar->setSpacing(0);
    vBoxEditBar->addSpacing(17);
    vBoxEditBar->addWidget(btnTailor);
    vBoxEditBar->addSpacing(22);
    vBoxEditBar->addWidget(btnRotate);
    vBoxEditBar->addSpacing(22);
    vBoxEditBar->addWidget(btnSymmetry);
    vBoxEditBar->addSpacing(22);
    vBoxEditBar->addWidget(btnWatermark);
    vBoxEditBar->addSpacing(17);
    vBoxEditBar->setContentsMargins(5,0,5,0);
    setLayout(vBoxEditBar);

}
