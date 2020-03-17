#include "scan_set.h"

ScanSet::ScanSet(QWidget *parent)
    : QWidget(parent)
{

    labDevice = new QLabel();
    labType = new QLabel();
    labColor = new QLabel();
    labResalution = new QLabel();
    labSize = new QLabel();
    labFormat = new QLabel();
    labName = new QLabel() ;
    labLocation = new QLabel();

    line3 = new QLabel();
    line4 = new QLabel();

    textDevice = new QLabel();
    textType = new QLabel();
    textColor = new QComboBox();
    textResalution = new QComboBox();
    textSize = new QComboBox();
    textFormat = new QComboBox();
    textName = new QLabel();
    textLocation = new QComboBox();

    hBoxDevice = new QHBoxLayout();
    hBoxType = new QHBoxLayout();
    hBoxColor = new QHBoxLayout();
    hBoxResalution = new QHBoxLayout();
    hBoxSize = new QHBoxLayout();
    hBoxFormat = new QHBoxLayout();
    hBoxName = new QHBoxLayout();
    hBoxLocation = new QHBoxLayout();

    vBoxScanSet = new QVBoxLayout();
//    vBoxScanSet1 = new QVBoxLayout(this);
    hBoxScanSet = new QHBoxLayout(this);

    labDevice->setText("设备");
    labDevice->setAlignment(Qt::AlignRight);
    labDevice->setStyleSheet("color:rgb(232,232,232)");
    labDevice->setFixedSize(40,32);

    labType->setText("类型");
    labType->setAlignment(Qt::AlignRight);
    labType->setStyleSheet("color:rgb(232,232,232)");
    labType->setFixedSize(40,32);

    labColor->setText("色彩");
    labColor->setAlignment(Qt::AlignRight);
    labColor->setStyleSheet("color:rgb(232,232,232)");
    labColor->setFixedSize(40,32);

    labResalution->setText("分辨率");
    labResalution->setAlignment(Qt::AlignRight);
    labResalution->setStyleSheet("color:rgb(232,232,232)");
    labResalution->setFixedSize(40,32);

    labSize->setText("尺寸");
    labSize->setAlignment(Qt::AlignRight);
    labSize->setStyleSheet("color:rgb(232,232,232)");
    labSize->setFixedSize(40,32);

    labFormat->setText("格式");
    labFormat->setAlignment(Qt::AlignRight);
    labFormat->setStyleSheet("color:rgb(232,232,232)");
    labFormat->setFixedSize(40,32);

    labName->setText("名称");
    labName->setAlignment(Qt::AlignRight);
    labName->setStyleSheet("color:rgb(232,232,232)");
    labName->setFixedSize(40,32);

    labLocation->setText("扫描至");
    labLocation->setAlignment(Qt::AlignRight);
    labLocation->setStyleSheet("color:rgb(232,232,232)");
    labLocation->setFixedSize(40,32);




    textDevice->setText("无可用设备");
    textDevice->setStyleSheet("QLabel{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textDevice->setFixedSize(180,32);

    textType->setText("平板式");
    textType->setStyleSheet("QLabel{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textType->setFixedSize(180,32);

    QStringList strList1, strList2, strList3, strList4,strList5;

    textColor->clear();
    strList1<<"灰度"<<"黑白"<<"彩色";
    textColor->setStyleSheet("QComboBox{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textColor->addItems(strList1);
    textColor->setFixedSize(180,32);

    textResalution->clear();
    strList2<<"4800dpi"<<"2400dpi"<<"1200dpi"<<"600dpi"<<"300dpi"<<"自动";
    textResalution->setStyleSheet("QComboBox{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textResalution->addItems(strList2);
    textResalution->setFixedSize(180,32);

    textSize->clear();
    strList3<<"A4"<<"A3";
    textSize->setStyleSheet("QComboBox{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textSize->addItems(strList3);
    textSize->setFixedSize(180,32);

    textFormat->clear();
    strList4<<"jpg"<<"png"<<"pdf"<<"bmp"<<"rtf";
    textFormat->setStyleSheet("QComboBox{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textFormat->addItems(strList4);
    textFormat->setFixedSize(180,32);

    textName->setText("扫描文件名");
    textName->setStyleSheet("QLabel{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textName->setFixedSize(180,32);

    textLocation->clear();
    strList5<<"本地磁盘"<<"外接设备";
    textLocation->setStyleSheet("QComboBox{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textLocation->addItems(strList5);
    textLocation->setFixedSize(180,32);

    hBoxDevice->addWidget(labDevice);
    hBoxDevice->setSpacing(14);
    hBoxDevice->addWidget(textDevice);
    hBoxDevice->setContentsMargins(16,0,16,4);
    hBoxDevice->addStretch();

    hBoxType->addWidget(labType);
    hBoxType->addSpacing(8);
    hBoxType->addWidget(textType);
    hBoxType->setContentsMargins(16,4,16,4);
    hBoxType->addStretch();

    hBoxColor->addWidget(labColor);
    hBoxColor->addSpacing(8);
    hBoxColor->addWidget(textColor);
    hBoxColor->setContentsMargins(16,4,16,4);
    hBoxColor->addStretch();

    hBoxResalution->addWidget(labResalution);
    hBoxResalution->addSpacing(8);
    hBoxResalution->addWidget(textResalution);
    hBoxResalution->setContentsMargins(16,4,16,4);
    hBoxResalution->addStretch();

    hBoxSize->addWidget(labSize);
    hBoxSize->addSpacing(8);
    hBoxSize->addWidget(textSize);
    hBoxSize->setContentsMargins(16,4,16,4);
    hBoxSize->addStretch();

    hBoxFormat->addWidget(labFormat);
    hBoxFormat->addSpacing(8);
    hBoxFormat->addWidget(textFormat);
    hBoxFormat->setContentsMargins(16,4,16,4);
    hBoxFormat->addStretch();

    hBoxName->addWidget(labName);
    hBoxName->addSpacing(8);
    hBoxName->addWidget(textName);
    hBoxName->setContentsMargins(16,4,16,4);
    hBoxName->addStretch();

    hBoxLocation->addWidget(labLocation);
    hBoxLocation->addSpacing(8);
    hBoxLocation->addWidget(textLocation);
    hBoxLocation->setContentsMargins(16,4,16,4);
    hBoxLocation->addStretch();

    vBoxScanSet->addLayout(hBoxDevice);
    vBoxScanSet->addLayout(hBoxType);
    vBoxScanSet->addLayout(hBoxColor);
    vBoxScanSet->addLayout(hBoxResalution);
    vBoxScanSet->addLayout(hBoxSize);
    vBoxScanSet->addLayout(hBoxFormat);
    vBoxScanSet->addLayout(hBoxName);
    vBoxScanSet->addLayout(hBoxLocation);
    vBoxScanSet->addStretch();
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(32, 30, 29));
    setAutoFillBackground(true);
    setPalette(pal);

    hBoxScanSet->addLayout(vBoxScanSet);
    hBoxScanSet->addStretch();
    hBoxScanSet->addSpacing(600);
    hBoxScanSet->addStretch();
    setLayout(hBoxScanSet);
}

ScanSet::~ScanSet()
{

}
