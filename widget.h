#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPdfWriter>
#include <QPainter>
#include "scan_display.h"
#include <scan_set.h>
#include "title_bar.h"
#include "func_bar.h"
class Widget : public QWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = 0);
    ~Widget();
    void set_pdf_size(QPdfWriter *pdfWriter,QString size);
    void save_to_pdf(QImage img, QString pathName);

private:
    TitleBar *pTitleBar;
    QFrame *line;
    FuncBar *pFuncBar;
    ScanSet *pScanSet;
    scan_display *pScandisplay;
    QHBoxLayout *pHboxLayout;
    QVBoxLayout *pLayout;
private slots:
    void save_image(QString fileName);
    void save_scan_file();



};

#endif // WIDGET_H
