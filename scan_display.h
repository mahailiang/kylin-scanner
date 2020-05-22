#ifndef SCAN_DISPLAY_H
#define SCAN_DISPLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QImage>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QInputDialog>
#include <qmath.h>
#include <QStack>
#include <QThread>
#include <QScrollArea>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "my_label.h"
#include "mark_dialog.h"
#include "func_bar.h"
#include <QWidget>
class myThread : public QThread
{
    Q_OBJECT
public:
    void run() Q_DECL_OVERRIDE;
signals:
    void orcFinished();
};
class edit_bar  :   public QWidget
{
    Q_OBJECT
public:
    edit_bar(QWidget *parent = nullptr);
//private:
    QPushButton *btnTailor;
    QPushButton *btnRotate;
    QPushButton *btnSymmetry;
    QPushButton *btnWatermark;
    QVBoxLayout *vBoxEditBar;
};

class scan_display  : public QWidget
{
    Q_OBJECT
public:
    scan_display(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *e);
    void imageSave(QString fileName);
    int flag = 0;
    int flag1 = 0;
    int index = 0;
    int n = 0;

private:
    QLabel *labDisplay1;
    QLabel *labDisplay2;
    QLabel *labDisplay3;
    QLabel *labDisplay4;
    QLabel *labDisplay5;
    QLabel *labDisplay6;
    QLabel *labDisplay7;
    my_label *labDisplay8;
    QLabel *labDisplay9;
    QLabel *labDisplay10;
    QPushButton *btnTool;
    QPushButton *btnTool1;
    QPushButton *btnTool2;

    QImage *img;
    QImage *img1;
    QImage *img2;
    QImage *img3;
    QImage *img4;
    QImage *img5;
    QImage *img6;
    QImage *img7;
    QStack<QImage> stack;
    QVBoxLayout *vBoxScanSet;
    QVBoxLayout *vBoxScanSet1;
    QVBoxLayout *vBoxScanSet2;
    QVBoxLayout *vBoxScanSet3;
    QHBoxLayout *hBoxScanSet;
    QHBoxLayout *hBoxScanSet1;
    QHBoxLayout *hBoxScanSet2;
    QHBoxLayout *hBoxScanSet3;
    QWidget *myWidget;
    QWidget *myWidget1;
    QWidget *myWidget2;
    QWidget *myWidget3;
    QWidget *myWidget4;
    QStackedLayout *vStackedLayout;
    edit_bar *editlayout;
    edit_bar *editlayout1;
    edit_bar *editlayout2;
    myThread thread;
    QScrollArea *scrollArea;
    int widgetindex;
//signals:
//    void indexChanged(int value);
private slots:
    void switchPage();
    void switchPage1();
    void rotating();
    void symmetry();
    void addmark();
    void orcText();
public slots:
    void orc();
};

#endif // SCAN_DISPLAY_H
