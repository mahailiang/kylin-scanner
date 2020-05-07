#ifndef SCAN_DISPLAY_H
#define SCAN_DISPLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QImage>
#include <QPushButton>
#include "my_label.h"
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
    int flag = 0;
    int index = 0;
//    int n = 0;
private:
    QLabel *labDisplay1;
    QLabel *labDisplay2;
    QLabel *labDisplay3;
    QLabel *labDisplay4;
    QLabel *labDisplay5;
    QLabel *labDisplay6;
    QLabel *labDisplay7;
    my_label *labDisplay8;
    QPushButton *btnTool;
    QPushButton *btnTool1;
    QPushButton *btnTool2;

    QImage *img;
    QImage *img1;
    QImage *img2;
    QImage *img3;
    QImage *img4;
    QImage *img5;
    QVBoxLayout *vBoxScanSet;
    QVBoxLayout *vBoxScanSet1;
    QVBoxLayout *vBoxScanSet2;
    QHBoxLayout *hBoxScanSet;
    QHBoxLayout *hBoxScanSet1;
    QHBoxLayout *hBoxScanSet2;
    QWidget *myWidget;
    QWidget *myWidget1;
    QWidget *myWidget2;
    QWidget *myWidget3;
    QStackedLayout *vStackedLayout;
    edit_bar *editlayout;
    edit_bar *editlayout1;
signals:
    void indexChanged(int value);
private slots:
    void switchPage();
    void switchPage1();
    void rotating();

};


#endif // SCAN_DISPLAY_H
