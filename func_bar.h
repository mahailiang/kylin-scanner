#ifndef FUNC_BAR_H
#define FUNC_BAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>


class FuncBar : public QWidget
{
    Q_OBJECT

public:
    explicit FuncBar(QWidget *parent = nullptr);
    ~FuncBar();

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


};

#endif // FUNC_BAR_H
