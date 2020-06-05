#ifndef FUNC_BAR_H
#define FUNC_BAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QInputEvent>

#include "kylin_sane.h"

class FuncBar : public QWidget
{
    Q_OBJECT

public:
    explicit FuncBar(QWidget *parent = nullptr);
    ~FuncBar();
    void keyPressEvent(QKeyEvent *e);
    int n = 0;


private:
    QPushButton *btnNorScan ;
    QPushButton *btnBeautify;
    QPushButton *btnRectify;
    QPushButton *btnOrc;
    QPushButton *btnScan;
    QLabel *labNorScan;
    QLabel *labBeautify;
    QLabel *labRectify;
    QLabel *labOrc;
    QFrame *line1;
    QFrame *line2;
    QVBoxLayout *vBoxLay1;
    QVBoxLayout *vBoxLay2;
    QVBoxLayout *vBoxLay3;
    QVBoxLayout *vBoxLay4;
    QHBoxLayout *hBoxLay1;
    QHBoxLayout *hBoxLay2;
    QHBoxLayout *hBoxLay3;
    QHBoxLayout *hBoxLay4;

private slots:
    void on_btnOrc_clicked();
    void on_btnScan_clicked();

Q_SIGNALS:
    void send_Orc_Begin();
    void send_Orc_End();
    void send_Scan_End();

};
#endif // FUNC_BAR_H
