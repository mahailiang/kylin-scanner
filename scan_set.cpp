#include "scan_set.h"

ScanSet::ScanSet(QWidget *parent)
    : QWidget(parent)
{

    setFixedWidth(260);
  //  setFixedHeight(567);
    labDevice = new QLabel();
    labType = new QLabel();
    labColor = new QLabel();
    labResalution = new QLabel();
    labSize = new QLabel();
    labFormat = new QLabel();
    labName = new QLabel() ;
    labLocation = new QLabel();

    line3 = new QFrame();
    line4 = new QFrame();

    btnMail = new QPushButton();
    btnText = new QPushButton();

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
    hBoxLine3 = new QHBoxLayout();
    hBoxLine4 = new QHBoxLayout();
    hBoxMailText = new QHBoxLayout();

    vBoxScanSet = new QVBoxLayout(this);
    hBoxScanSet = new QHBoxLayout(this);

    line3 = new QFrame();
    line3->setObjectName(QString::fromUtf8("line3"));
    line3->setMaximumHeight(1);
    line3->setMaximumWidth(230);
    line3->setMinimumWidth(230);
    line3->setFrameShape(QFrame::HLine);
    line3->setStyleSheet("QLabel{color:rgb(32,30,29)}");

    line4 = new QFrame();
    line4->setObjectName(QString::fromUtf8("line4"));
    line4->setMaximumHeight(1);
    line4->setMaximumWidth(230);
    line4->setMinimumWidth(230);
    line4->setFrameStyle(QFrame::HLine);
    line4->setStyleSheet("QLabel{color:rgb(32,30,29)}");

    btnMail->setText("发送至邮件");
    btnMail->setFixedSize(120,32);
    btnText->setText("存储文本");
    btnText->setFixedSize(100,32);


    btnMail->setStyleSheet("QPushButton{background-color:rgb(32,30,29);border:1px solid #939393;color:rgb(232,232,232);border-radius:16px;}"
                              "QPushButton:hover{border:none;background-color:rgb(39,208,127);border:rgb(147,147,147);color:rgb(232,232,232);border-radius:16px;}"
                                "QPushButton:checked{border:none;background-color:rgb(39,208,127);border:rgb(147,147,147);color:rgb(232,232,232);border-radius:16px;}");
    btnText->setStyleSheet("QPushButton{background-color:rgb(32,30,29);border:1px solid #939393;color:rgb(232,232,232);border-radius:16px;}"
                              "QPushButton:hover{border:none;background-color:rgb(39,208,127);color:rgb(232,232,232);border-radius:16px;}"
                                "QPushButton:checked{border:none;background-color:rgb(39,208,127);color:rgb(232,232,232)border-radius:16px;}");

    labDevice->setText("设备");
    labDevice->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labDevice->setStyleSheet("color:rgb(232,232,232)");
    labDevice->setFixedSize(40,32);

    labType->setText("类型");
    labType->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labType->setStyleSheet("color:rgb(232,232,232)");
    labType->setFixedSize(40,32);

    labColor->setText("色彩");
    labColor->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labColor->setStyleSheet("color:rgb(232,232,232)");

    labColor->setFixedSize(40,32);

    labResalution->setText("分辨率");
    labResalution->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labResalution->setStyleSheet("color:rgb(232,232,232)");
    labResalution->setFixedSize(40,32);

    labSize->setText("尺寸");
    labSize->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labSize->setStyleSheet("color:rgb(232,232,232)");
    labSize->setFixedSize(40,32);

    labFormat->setText("格式");
    labFormat->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labFormat->setStyleSheet("color:rgb(232,232,232)");
    labFormat->setFixedSize(40,32);

    labName->setText("名称");
    labName->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    labName->setStyleSheet("color:rgb(232,232,232)");
    labName->setFixedSize(40,32);

    labLocation->setText("扫描至");
    labLocation->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
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
 //   textColor->setStyleSheet("QComboBox{background-color:rgb(0f,08,01);color:rgb(232,232,232);border-radius:6px;}");
//    textColor->setStyleSheet("QComboBox{border:0px solid gray;background:#0d0400;font:14px;color:#e8e8e8;height: 32px;border-radius:6px;}"
//                                "QComboBox QAbstractItemView{border: 2px;outline:2px;selection-background-color: #6f6f6f;height:32px;background: red;font:14px;color:red;}"
//                                "QComboBox QAbstractItemView::item{height:32px;}"
//                                "QComboBox QAbstractItemView::item:selected{background-color: red;}"
//                                "QComboBox::down-arrow{image:url(:/icon_home_trangle.png);}"
//                                "QComboBox::drop-down{border:4px;}"
//                                );

    textColor->setStyleSheet(
                "QComboBox{border-radius:4px;background-color:#0D0400;color:#e8e8e8;}"
                "QComboBox::drop-down{subcontrol-position: top right;border-radius: 4px;}" //下拉按钮
                "QComboBox::down-arrow{border-image:url(:/icon/icon/down.png);}"//下拉箭头
                "QComboBox QAbstractItemView{margin-top:4px solid #0D0400;color:#e8e8e8;border-radius:4px;background-color:#888888;}"
                "QComboBox QAbstractItemView::item{width:180px;height: 32px;border-radius:4px;}"//下拉选项样式
                "QComboBox QAbstractItemView::item:hover{background-color:#6F6F6F;}"
                "QComboBox QAbstractItemView::item:selected{background-color:#6F6F6F;}"
                );
    textColor->addItems(strList1);
    textColor->setFixedSize(180,32);
    textColor->setInsertPolicy(QComboBox::NoInsert);  //编辑框的内容不插入到列表项
    QListView *colorListView = new QListView;
    textColor->setEditable( true ); //可编辑
    textColor->setFocusPolicy(Qt::NoFocus); //获取焦点策略：无焦点，也就是不可编辑
    textColor->setModel(colorListView->model());
    textColor->setView(colorListView); //使下拉选项样式生效

    textResalution->clear();
    strList2<<"4800dpi"<<"2400dpi"<<"1200dpi"<<"600dpi"<<"300dpi"<<"自动";
//    textResalution->setStyleSheet("QComboBox{background-color:rgb(0f,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textResalution->setStyleSheet(
                "QComboBox{border-radius:4px;background-color:#0D0400;color:#e8e8e8;}"
                "QComboBox::drop-down{subcontrol-position: top right;border-radius: 4px;}" //下拉按钮
                "QComboBox::down-arrow{border-image:url(:/icon/icon/down.png);}"//下拉箭头
                "QComboBox QAbstractItemView{margin-top:4px solid #0D0400;color:#e8e8e8;border-radius:4px;background-color:#888888;}"
                "QComboBox QAbstractItemView::item{width:180px;height: 32px;border-radius:4px;}"//下拉选项样式
                "QComboBox QAbstractItemView::item:hover{background-color:#6F6F6F;}"
                "QComboBox QAbstractItemView::item:selected{background-color:#6F6F6F;}"
                );
    textResalution->addItems(strList2);
    textResalution->setFixedSize(180,32);
    textResalution->setInsertPolicy(QComboBox::NoInsert);  //编辑框的内容不插入到列表项
    QListView *resalutionListView = new QListView;
    textResalution->setEditable( true ); //可编辑
    textResalution->setFocusPolicy(Qt::NoFocus); //获取焦点策略：无焦点，也就是不可编辑
    textResalution->setModel(resalutionListView->model());
    textResalution->setView(resalutionListView); //使下拉选项样式生效

    textSize->clear();
    strList3<<"A4"<<"A3";
//    textSize->setStyleSheet("QComboBox{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textSize->setStyleSheet(
                "QComboBox{border-radius:4px;background-color:#0D0400;color:#e8e8e8;}"
                "QComboBox::drop-down{subcontrol-position: top right;border-radius: 4px;}" //下拉按钮
                "QComboBox::down-arrow{border-image:url(:/icon/icon/down.png);}"//下拉箭头
                "QComboBox QAbstractItemView{margin-top:4px solid #0D0400;color:#e8e8e8;border-radius:4px;background-color:#888888;}"
                "QComboBox QAbstractItemView::item{width:180px;height: 32px;border-radius:4px;}"//下拉选项样式
                "QComboBox QAbstractItemView::item:hover{background-color:#6F6F6F;}"
                "QComboBox QAbstractItemView::item:selected{background-color:#6F6F6F;}"
                );
    textSize->addItems(strList3);
    textSize->setFixedSize(180,32);
    textSize->setInsertPolicy(QComboBox::NoInsert);  //编辑框的内容不插入到列表项
    QListView *sizeListView = new QListView;
    textSize->setEditable( true ); //可编辑
    textSize->setFocusPolicy(Qt::NoFocus); //获取焦点策略：无焦点，也就是不可编辑
    textSize->setModel(sizeListView->model());
    textSize->setView(sizeListView); //使下拉选项样式生效

    textFormat->clear();
    strList4<<"jpg"<<"png"<<"pdf"<<"bmp"<<"rtf";
//    textFormat->setStyleSheet("QComboBox{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textFormat->setStyleSheet(
                "QComboBox{border-radius:4px;background-color:#0D0400;color:#e8e8e8;}"
                "QComboBox::drop-down{subcontrol-position: top right;border-radius: 4px;}" //下拉按钮
                "QComboBox::down-arrow{border-image:url(:/icon/icon/down.png);}"//下拉箭头
                "QComboBox QAbstractItemView{margin-top:4px solid #0D0400;color:#e8e8e8;border-radius:4px;background-color:#888888;}"
                "QComboBox QAbstractItemView::item{width:180px;height: 32px;border-radius:4px;}"//下拉选项样式
                "QComboBox QAbstractItemView::item:hover{background-color:#6F6F6F;}"
                "QComboBox QAbstractItemView::item:selected{background-color:#6F6F6F;}"
                );
    textFormat->addItems(strList4);
    textFormat->setFixedSize(180,32);
    textFormat->setInsertPolicy(QComboBox::NoInsert);  //编辑框的内容不插入到列表项
    QListView *formatListView = new QListView;
    textFormat->setEditable( true ); //可编辑
    textFormat->setFocusPolicy(Qt::NoFocus); //获取焦点策略：无焦点，也就是不可编辑
    textFormat->setModel(formatListView->model());
    textFormat->setView(formatListView); //使下拉选项样式生效

    textName->setText("扫描文件名");
    textName->setStyleSheet("QLabel{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textName->setFixedSize(180,32);

    textLocation->clear();
    strList5<<"本地磁盘"<<"外接设备";
//    textLocation->setStyleSheet("QComboBox{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textLocation->setStyleSheet(
                "QComboBox{border-radius:4px;background-color:#0D0400;color:#e8e8e8;}"
                "QComboBox::drop-down{subcontrol-position: top right;border-radius: 4px;}" //下拉按钮
                "QComboBox::down-arrow{border-image:url(:/icon/icon/down.png);}"//下拉箭头
                "QComboBox QAbstractItemView{margin-top:4px solid #0D0400;color:#e8e8e8;border-radius:4px;background-color:#888888;}"
                "QComboBox QAbstractItemView::item{width:180px;height: 32px;border-radius:4px;}"//下拉选项样式
                "QComboBox QAbstractItemView::item:hover{background-color:#6F6F6F;}"
                "QComboBox QAbstractItemView::item:selected{background-color:#6F6F6F;}"
                );
    textLocation->addItems(strList5);
    textLocation->setFixedSize(180,32);
    textFormat->setInsertPolicy(QComboBox::NoInsert);  //编辑框的内容不插入到列表项
    QListView *locationListView = new QListView;
    textLocation->setEditable( true ); //可编辑
    textLocation->setFocusPolicy(Qt::NoFocus); //获取焦点策略：无焦点，也就是不可编辑
    textLocation->setModel(locationListView->model());
    textLocation->setView(locationListView); //使下拉选项样式生效


    hBoxDevice->setSpacing(0);
 //   hBoxDevice->addSpacing(16);
    hBoxDevice->addWidget(labDevice);
    hBoxDevice->addSpacing(8);
    hBoxDevice->addWidget(textDevice);
//    hBoxDevice->addSpacing(16);
    hBoxDevice->setContentsMargins(0,24,0,4);


    hBoxType->setSpacing(0);
 //   hBoxType->addSpacing(16);
    hBoxType->addWidget(labType);
    hBoxType->addSpacing(8);
    hBoxType->addWidget(textType);
//    hBoxType->addSpacing(16);
    hBoxType->setContentsMargins(0,4,0,4);

    hBoxColor->setSpacing(0);
 //   hBoxColor->addSpacing(16);
    hBoxColor->addWidget(labColor);
    hBoxColor->addSpacing(8);
    hBoxColor->addWidget(textColor);
 //   hBoxColor->addSpacing(16);
    hBoxColor->setContentsMargins(0,4,0,4);

    hBoxResalution->setSpacing(0);
//    hBoxResalution->addSpacing(16);
    hBoxResalution->addWidget(labResalution);
    hBoxResalution->addSpacing(8);
    hBoxResalution->addWidget(textResalution);
 //   hBoxResalution->addSpacing(16);
    hBoxResalution->setContentsMargins(0,4,0,4);

    hBoxSize->setSpacing(0);
 //   hBoxSize->addSpacing(16);
    hBoxSize->addWidget(labSize);
    hBoxSize->addSpacing(8);
    hBoxSize->addWidget(textSize);
//    hBoxSize->addSpacing(16);
    hBoxSize->setContentsMargins(0,4,0,16);

    hBoxFormat->setSpacing(0);
//    hBoxFormat->addSpacing(16);
    hBoxFormat->addWidget(labFormat);
    hBoxFormat->addSpacing(8);
    hBoxFormat->addWidget(textFormat);
 //   hBoxFormat->addSpacing(16);
    hBoxFormat->setContentsMargins(0,16,0,4);

    hBoxName->setSpacing(0);
 //   hBoxName->addSpacing(16);
    hBoxName->addWidget(labName);
    hBoxName->addSpacing(8);
    hBoxName->addWidget(textName);
//    hBoxName->addSpacing(16);
    hBoxName->setContentsMargins(0,4,0,4);

    hBoxLocation->setSpacing(0);
//    hBoxLocation->addSpacing(16);
    hBoxLocation->addWidget(labLocation);
    hBoxLocation->addSpacing(8);
    hBoxLocation->addWidget(textLocation);
//    hBoxLocation->addSpacing(16);
    hBoxLocation->setContentsMargins(0,4,0,4);

    hBoxLine3->setSpacing(0);
 //   hBoxLine3->addSpacing(15);
    hBoxLine3->addWidget(line3);
//    hBoxLine3->addSpacing(15);
    hBoxLine3->setContentsMargins(0,0,0,0);

    hBoxLine4->setSpacing(0);
//    hBoxLine4->addSpacing(15);
    hBoxLine4->addWidget(line4);
//    hBoxLine4->addSpacing(15);
    hBoxLine4->setContentsMargins(0,112,0,0);

    hBoxMailText->setSpacing(0);
//    hBoxMailText->addSpacing(15);
    hBoxMailText->addWidget(btnMail);
    hBoxMailText->addSpacing(10);
    hBoxMailText->addWidget(btnText);
 //   hBoxMailText->addSpacing(15);
    hBoxMailText->setContentsMargins(0,20,0,20);


    vBoxScanSet->setSpacing(0);
    vBoxScanSet->addLayout(hBoxDevice);
    vBoxScanSet->addLayout(hBoxType);
    vBoxScanSet->addLayout(hBoxColor);
    vBoxScanSet->addLayout(hBoxResalution);
    vBoxScanSet->addLayout(hBoxSize);
    vBoxScanSet->addLayout(hBoxLine3);
    vBoxScanSet->addLayout(hBoxFormat);
    vBoxScanSet->addLayout(hBoxName);
    vBoxScanSet->addLayout(hBoxLocation);
//    vBoxScanSet->addStretch();
//    vBoxScanSet->addSpacing(205);
    vBoxScanSet->addStretch();
    vBoxScanSet->addLayout(hBoxLine4);
    vBoxScanSet->addLayout(hBoxMailText);
  //  vBoxScanSet->addStretch(5);


    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(32, 30, 29));
    setAutoFillBackground(true);
    setPalette(pal);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    hBoxScanSet->setSpacing(0);
    hBoxScanSet->addLayout(vBoxScanSet);
//    hBoxScanSet->addStretch();
//    hBoxScanSet->addSpacing(0);
    hBoxScanSet->addStretch();
    setLayout(hBoxScanSet);
}

ScanSet::~ScanSet()
{

}
