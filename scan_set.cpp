#include "scan_set.h"
QString curPath;
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
    btnSave = new QPushButton();
    btnLocation = new QPushButton();

    textDevice = new QLabel();
    textType = new QLabel();
    textColor = new KylinComboBox();
    textResalution = new KylinComboBox();
    textSize = new KylinComboBox();
    textFormat = new KylinComboBox();
    textName = new QLineEdit();

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
    btnSave->setText("另存为");
    btnSave->setFixedSize(100,32);

    QFontMetrics elideFont(btnLocation->font());
    if(curPath.isEmpty())
        curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径
    btnLocation->setText(elideFont.elidedText(curPath,Qt::ElideRight,150));
    btnLocation->setFixedSize(180,32);



    btnMail->setStyleSheet("QPushButton{background-color:rgb(32,30,29);border:1px solid #939393;color:rgb(232,232,232);border-radius:16px;}"
                              "QPushButton:hover{border:none;background-color:rgb(39,208,127);border:rgb(147,147,147);color:rgb(232,232,232);border-radius:16px;}"
                                "QPushButton:checked{border:none;background-color:rgb(39,208,127);border:rgb(147,147,147);color:rgb(232,232,232);border-radius:16px;}");
    btnSave->setStyleSheet("QPushButton{background-color:rgb(32,30,29);border:1px solid #939393;color:rgb(232,232,232);border-radius:16px;}"
                              "QPushButton:hover{border:none;background-color:rgb(39,208,127);color:rgb(232,232,232);border-radius:16px;}"
                                "QPushButton:checked{border:none;background-color:rgb(39,208,127);color:rgb(232,232,232)border-radius:16px;}");
    btnLocation->setStyleSheet("QPushButton{background-image:url(:/icon/icon/max.png);border:none;background-repeat:no-repeat;background-position:right;background-color:#0D0400;color:rgb(232,232,232);border-radius:6px;text-align:left;}");


    setKylinLable();
    setKylinComboBox();
    setKylinHBoxLayout();




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
    vBoxScanSet->setContentsMargins(0,0,0,0);
  //  vBoxScanSet->addStretch(5);


    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(32, 30, 29));
    setAutoFillBackground(true);
    setPalette(pal);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    hBoxScanSet->setSpacing(0);
//    hBoxScanSet->addLayout(vBoxScanSet);
//    hBoxScanSet->addStretch();
//    hBoxScanSet->addSpacing(0);
//    hBoxScanSet->addStretch();
    setLayout(vBoxScanSet);
    connect(btnLocation,SIGNAL(clicked()),this,SLOT(on_btnLocation_clicked()));
}

ScanSet::~ScanSet()
{

}

void ScanSet::setKylinComboBoxAttributes(KylinComboBox *combo, QStringList strList)
{
    QListView *listView = new QListView;

    combo->clear();
    combo->addItems(strList);
    combo->setFixedSize(180,32);
    combo->setInsertPolicy(QComboBox::NoInsert);  //编辑框的内容不插入到列表项
    combo->setFocusPolicy(Qt::NoFocus); //获取焦点策略：无焦点，也就是不可编辑
    combo->setModel(listView->model());
    combo->setView(listView);   //使下拉选项样式生效
}

void ScanSet::setKylinComboBox()
{
    QStringList strListColor, strListResalution, strListFormat, strListSize,strListLocation;

    strListColor<<tr("灰度")<<tr("黑白")<<tr("彩色");
    setKylinComboBoxAttributes(textColor, strListColor);

    strListResalution<<tr("4800dpi")<<tr("2400dpi")<<tr("1200dpi")<<tr("600dpi")<<tr("300dpi")<<tr("自动");
    setKylinComboBoxAttributes(textResalution, strListResalution);

    strListSize<<tr("A4")<<tr("A3");
    setKylinComboBoxAttributes(textSize, strListSize);

    strListFormat<<tr("jpg")<<tr("png")<<tr("pdf")<<tr("bmp")<<tr("rtf");
    setKylinComboBoxAttributes(textFormat, strListFormat);

//    strListLocation<<"本地磁盘"<<"外接设备";
//    setKylinComboBoxAttributes(textLocation, strListLocation);
}

void ScanSet::setKylinLable()
{
    labDevice->setText("设备");
    setKylinLabelAttributes(labDevice);

    labType->setText("类型");
    setKylinLabelAttributes(labType);

    labColor->setText("色彩");
    setKylinLabelAttributes(labColor);

    labResalution->setText("分辨率");
    setKylinLabelAttributes(labResalution);

    labSize->setText("尺寸");
    setKylinLabelAttributes(labSize);

    labFormat->setText("格式");
    setKylinLabelAttributes(labFormat);

    labName->setText("名称");
    setKylinLabelAttributes(labName);

    labLocation->setText("扫描至");
    setKylinLabelAttributes(labLocation);

    textDevice->setText("无可用设备");
    textDevice->setStyleSheet("QLabel{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textDevice->setFixedSize(180,32);

    textType->setText("平板式");
    textType->setStyleSheet("QLabel{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textType->setFixedSize(180,32);

    textName->setText("扫描文件名");
    textName->setStyleSheet("QLineEdit{background-color:rgb(15,08,01);color:rgb(232,232,232);border-radius:6px;}");
    textName->setFixedSize(180,32);
}

void ScanSet::setKylinLabelAttributes(QLabel *label)
{
    label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    label->setStyleSheet("color:rgb(232,232,232)");
    label->setFixedSize(40,32);
}


void ScanSet::setKylinHBoxLayout()
{
    setKylinHBoxLayoutAttributes(hBoxDevice, labDevice, textDevice);
    hBoxDevice->setContentsMargins(0,24,0,4);

    setKylinHBoxLayoutAttributes(hBoxType, labType, textType);
    hBoxType->setContentsMargins(0,4,0,4);

    setKylinHBoxLayoutAttributes(hBoxColor, labColor, textColor);
    hBoxColor->setContentsMargins(0,4,0,4);

    setKylinHBoxLayoutAttributes(hBoxResalution, labResalution, textResalution);
    hBoxResalution->setContentsMargins(0,4,0,4);

    setKylinHBoxLayoutAttributes(hBoxSize, labSize, textSize);
    hBoxSize->setContentsMargins(0,4,0,16);

    setKylinHBoxLayoutAttributes(hBoxFormat, labFormat, textFormat);
    hBoxFormat->setContentsMargins(0,16,0,4);

    hBoxName->setSpacing(0);
    hBoxName->addWidget(labName);
    hBoxName->addSpacing(8);
    hBoxName->addWidget(textName);
//    setKylinHBoxLayoutAttributes(hBoxName, labName, textName);
    hBoxName->setContentsMargins(0,4,0,4);

//    setKylinHBoxLayoutAttributes(hBoxLocation, labLocation, btnLocation);
//    hBoxLocation->setContentsMargins(0,4,0,4);
    hBoxLocation->setSpacing(0);
    hBoxLocation->addWidget(labLocation);
    hBoxLocation->addSpacing(8);
    hBoxLocation->addWidget(btnLocation);
    hBoxLocation->setContentsMargins(0,4,0,4);

    hBoxLine3->setSpacing(0);
    hBoxLine3->addWidget(line3);
    hBoxLine3->setContentsMargins(0,0,0,0);

    hBoxLine4->setSpacing(0);
    hBoxLine4->addWidget(line4);
    hBoxLine4->setContentsMargins(0,112,0,0);

    hBoxMailText->setSpacing(0);
    hBoxMailText->addWidget(btnMail);
    hBoxMailText->addSpacing(10);
    hBoxMailText->addWidget(btnSave);
    hBoxMailText->setContentsMargins(0,20,0,20);

}

void ScanSet::setKylinHBoxLayoutAttributes(QHBoxLayout *layout, QLabel *labelFirst, QLabel *labelSecond)
{
    layout->setSpacing(0);
    layout->addWidget(labelFirst);
    layout->addSpacing(8);
    layout->addWidget(labelSecond);
//    layout->setContentsMargins(16,4,16,4);
//    layout->addStretch();
}

void ScanSet::setKylinHBoxLayoutAttributes(QHBoxLayout *layout, QLabel *labelFirst, KylinComboBox *combo)
{
    layout->setSpacing(0);
    layout->addWidget(labelFirst);
    layout->addSpacing(8);
    layout->addWidget(combo);
//    layout->setContentsMargins(16,4,16,4);
    //    layout->addStretch();
}

void ScanSet::on_btnLocation_clicked()
{
    if(curPath.isEmpty())
        curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径

    QString dlgTitle="选择一个目录"; //对话框标题
    QString selectedDir=QFileDialog::getExistingDirectory(this,dlgTitle,curPath,QFileDialog::ShowDirsOnly);
    if (!selectedDir.isEmpty())
    {
        QFontMetrics elideFont(btnLocation->font());
        btnLocation->setText(elideFont.elidedText(selectedDir,Qt::ElideRight,150));
    }
}

