#include "kylincombobox.h"

KylinComboBox::KylinComboBox(QWidget *parent) : QComboBox(parent)
{
    QComboBox::setStyleSheet(
                "QComboBox{border-radius:4px;background-color:#0D0400;color:white;}"
                "QComboBox QLineEdit{border-radios:4px;}"
                "QComboBox:hover{border-radius:4px;background-color:#0D0400;color:white;}"
                "QComboBox::drop-down{border-radius:4px;}" //下拉按钮
                "QComboBox::down-arrow{border-radius:4px;border-image:url(:/icon/icon/down.png);}"//下拉箭头
                "QComboBox QAbstractItemView{margin-top:4px solid #0D0400;color:white;border-radius:4px;background-color:#888888;}"
                "QComboBox QAbstractItemView::item{width:180px;height: 32px;border-radius:4px;}"//下拉列表框样式
                "QComboBox QAbstractItemView::item:hover:selected{background-color:#6F6F6F;}"
                );
    QComboBox::setEditable(false);
}
KylinComboBox::~KylinComboBox()
{

}

void KylinComboBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();  //触发clicked信号
    }

    QComboBox::mousePressEvent(event);  //将该事件传给父类处理，这句话很重要，如果没有，父类无法处理本来的点击事件
}

void KylinComboBox::hidePopup()
{
    QComboBox::setEditable(false);
    QComboBox::setStyleSheet(
                "QComboBox{border-radius:4px;background-color:#0D0400;color:white;}"
                "QComboBox QLineEdit{border-radios:4px;}"
                "QComboBox:hover{border-radius:4px;background-color:#0D0400;color:white;}"
                "QComboBox::drop-down{border-radius:4px;}" //下拉按钮
                "QComboBox::down-arrow{border-radius:4px;border-image:url(:/icon/icon/down.png);}"//下拉箭头
                "QComboBox QAbstractItemView{margin-top:4px solid #0D0400;color:white;border-radius:4px;background-color:#888888;}"
                "QComboBox QAbstractItemView::item{width:180px;height: 32px;border-radius:4px;}"//下拉列表框样式
                "QComboBox QAbstractItemView::item:hover:selected{background-color:#6F6F6F;}"
                );

    QComboBox::hidePopup();
}

void KylinComboBox::showPopup()
{
    QComboBox::setEditable(true);
    QComboBox::setStyleSheet(
                "QComboBox{border:2px solid blue;border-radius:4px;background-color:#0D0400;color:white;}"
                "QComboBox QLineEdit{border-radios:4px;}"
                "QComboBox:hover{border-radius:4px;background-color:#0D0400;color:white;}"
                "QComboBox::drop-down{border-radius:4px;}" //下拉按钮
                "QComboBox::down-arrow{border-radius:4px;border-image:url(:/icon/icon/down.png);}"//下拉箭头
                "QComboBox QAbstractItemView{margin-top:4px solid #0D0400;color:white;border-radius:4px;background-color:#888888;}"
                "QComboBox QAbstractItemView::item{width:180px;height: 32px;border-radius:4px;}"//下拉列表框样式
                "QComboBox QAbstractItemView::item:hover:selected{background-color:#6F6F6F;}"
                );

    QComboBox::showPopup();
}
