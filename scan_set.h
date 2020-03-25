#ifndef SCAN_SET_H
#define SCAN_SET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QListView>

class ScanSet  : public QWidget
{
    Q_OBJECT

public:
    explicit ScanSet(QWidget *parent = nullptr);
    ~ScanSet();

private:
    QLabel *labDevice;
    QLabel *labType;
    QLabel *labColor;
    QLabel *labResalution;
    QLabel *labSize;
    QLabel *labFormat;
    QLabel *labName;
    QLabel *labLocation;

    QFrame *line3;
    QFrame *line4;

    QPushButton *btnMail;
    QPushButton *btnText;

    QLabel *textDevice;
    QLabel *textType;
    QComboBox *textColor;
    QComboBox *textResalution;
    QComboBox *textSize;
    QComboBox *textFormat;
    QLabel *textName;
    QComboBox *textLocation;

    QHBoxLayout *hBoxDevice;
    QHBoxLayout *hBoxType;
    QHBoxLayout *hBoxColor;
    QHBoxLayout *hBoxResalution;
    QHBoxLayout *hBoxSize;
    QHBoxLayout *hBoxFormat;
    QHBoxLayout *hBoxName;
    QHBoxLayout *hBoxLocation;
    QHBoxLayout *hBoxLine3;
    QHBoxLayout *hBoxLine4;
    QHBoxLayout *hBoxMailText;
    QVBoxLayout *vBoxScanSet;
    QVBoxLayout *vBoxScanSet1;
    QHBoxLayout *hBoxScanSet;
};

#endif // SCAN_SET_H
