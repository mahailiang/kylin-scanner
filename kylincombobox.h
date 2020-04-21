#ifndef KYLINCOMBOBOX_H
#define KYLINCOMBOBOX_H

#include <QComboBox>
#include <QMouseEvent>

class KylinComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit KylinComboBox(QWidget *parent = nullptr);
    ~KylinComboBox();

protected:
    virtual void mousePressEvent(QMouseEvent *e);  //添加鼠标点击事件
    virtual void hidePopup(); //重载隐藏下拉框
    virtual void showPopup(); //重载显示下拉框


signals:
    void clicked();  //自定义点击信号，在mousePressEvent事件发生时触发

public slots:
};

#endif // KYLINCOMBOBOX_H
