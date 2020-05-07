#ifndef MY_LABEL_H
#define MY_LABEL_H
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QShowEvent>

class my_label  :   public QLabel
{
//    Q_OBJECT
public:
    my_label(QLabel *parent = nullptr);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    int x1, y1, x2, y2;

    void savePicture(QString path, int filename);

public:
    int getX1() {return x1;}
    int getY1() {return y1;}
    int getX2() {return x2;}
    int getY2() {return y2;}

};

#endif // MY_LABEL_H
