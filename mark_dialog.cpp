#include "mark_dialog.h"
#include <QPainter>
#include <QBitmap>
mark_dialog::mark_dialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setFixedSize(320,250);
    label = new QLabel();
    lineedit = new QLineEdit();
    line = new QFrame();
    btnOk = new QPushButton();
    btnCancel = new QPushButton();
    hBoxLayout = new QHBoxLayout();
    vBoxLayout = new QVBoxLayout(this);

    label->setText("输入水印内容");
    label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    label->setStyleSheet("color:rgb(232,232,232)");
    label->setFixedSize(192,32);
    QFont ft;
    ft.setPointSize(16);
    label->setFont(ft);

    lineedit->setText("");
    lineedit->setStyleSheet("QLineEdit{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    lineedit->setFixedSize(288,32);

    line = new QFrame();
    line->setObjectName(QString::fromUtf8("line"));
    line->setMaximumHeight(1);
    line->setMaximumWidth(288);
    line->setMinimumWidth(288);
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("QLabel{color:rgb(32,30,29)}");

    btnOk->setText("确定");
    btnOk->setFixedSize(120,36);
    btnCancel->setText("取消");
    btnCancel->setFixedSize(100,36);

    btnOk->setStyleSheet("QPushButton{background-color:rgb(32,30,29);border:1px solid #939393;color:rgb(232,232,232);border-radius:18px;}"
                              "QPushButton:hover{border:none;background-color:rgb(39,208,127);border:rgb(147,147,147);color:rgb(232,232,232);border-radius:18px;}"
                                "QPushButton:checked{border:none;background-color:rgb(39,208,127);border:rgb(147,147,147);color:rgb(232,232,232);border-radius:18px;}");
    btnCancel->setStyleSheet("QPushButton{background-color:rgb(32,30,29);border:1px solid #939393;color:rgb(232,232,232);border-radius:18px;}"
                              "QPushButton:hover{border:none;background-color:rgb(39,208,127);color:rgb(232,232,232);border-radius:18px;}"
                                "QPushButton:checked{border:none;background-color:rgb(39,208,127);color:rgb(232,232,232)border-radius:18px;}");

    hBoxLayout->setSpacing(0);
    hBoxLayout->addWidget(btnOk);
    hBoxLayout->addSpacing(16);
    hBoxLayout->addWidget(btnCancel);
    hBoxLayout->setContentsMargins(16,0,16,0);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(47, 44, 43));
    setAutoFillBackground(true);
    setPalette(pal);

    vBoxLayout->setSpacing(0);
    vBoxLayout->addWidget(label);
    vBoxLayout->addSpacing(32);
    vBoxLayout->addWidget(lineedit);
    vBoxLayout->addSpacing(22);
    vBoxLayout->addWidget(line);
    vBoxLayout->addSpacing(22);
    vBoxLayout->addLayout(hBoxLayout);
    vBoxLayout->setContentsMargins(16,30,16,30);

    QBitmap bitMap(width(),height()); // A bit map has the same size with current widget

    bitMap.fill();

    QPainter painter(&bitMap);

    painter.setBrush(Qt::black);

    painter.setPen(Qt::NoPen); // Any color that is not QRgb(0,0,0) is right

    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawRoundedRect(bitMap.rect(),6,6); //设置圆角弧度

    setMask(bitMap);

    setLayout(vBoxLayout);
    connect(btnOk,SIGNAL(clicked()),this,SLOT(accept()));
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(reject()));
}

mark_dialog::~mark_dialog()
{

}

QString mark_dialog::get_lineedit()
{
    return lineedit->text();
}
