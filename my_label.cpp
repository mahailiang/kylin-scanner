#include "my_label.h"
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QCursor>
#include <QApplication>
#include <QPixmap>
#include <QImage>

my_label::my_label(QLabel *parent)
{
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
}

void my_label::paintEvent(QPaintEvent *event)
{
    //comment before
    QLabel::paintEvent(event); //绘制背景的图片

    QPainter painter(this);

    painter.setPen(QPen(Qt::green, 1));
    painter.drawRect(QRect(x1, y1, x2 - x1, y2 - y1));
}

void my_label::mousePressEvent(QMouseEvent *event)
{
    x1 = event->pos().x();
    y1 = event->pos().y();
    QCursor cursor;
    cursor.setShape(Qt::ClosedHandCursor);
    QApplication::setOverrideCursor(cursor);
}

void my_label::mouseReleaseEvent(QMouseEvent *event)
{
    x2 = event->pos().x(); //鼠标相对于所在控件的位置
    y2 = event->pos().y();
    update();
    QApplication::restoreOverrideCursor();
}

void my_label::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        x2 = event->pos().x(); //鼠标相对于所在控件的位置
        y2 = event->pos().y();
        update();
    }
}





