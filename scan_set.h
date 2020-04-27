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
#include <QDialog>
#include <QFileDialog>
#include <QCoreApplication>
#include <QFont>
#include <QPixmap>
#include "kylincombobox.h"

class ScanSet  : public QWidget
{
    Q_OBJECT

public:
    explicit ScanSet(QWidget *parent = nullptr);
    ~ScanSet();

    /**
     * @brief setKylinComboBox 统一设置麒麟扫描组合框ComboBox
     */
    void setKylinComboBox();

    /**
     * @brief setKylinComboBoxAttributes 设置组合框属性
     * @param combo 需要属性设置的组合框
     * @param strList 组合框中文本框值
     */
    void setKylinComboBoxAttributes(KylinComboBox *combo, QStringList strList);

    /**
     * @brief setKylinLable 统一设置麒麟扫描标签Label
     */
    void setKylinLable();

    /**
     * @brief setKylinLabelAttributes 设置标签属性
     * @param label 需要属性设置的标签
     */
    void setKylinLabelAttributes(QLabel *label);

    /**
     * @brief setKylinHBoxLayout 统一设置麒麟扫描水平布局HBoxLayout
     */
    void setKylinHBoxLayout();

    /**
     * @brief setKylinHBoxLayoutAttributes 设置水平布局属性： 标签1和标签2
     * @param layout 需要设置的水平布局
     * @param labelFirst 水平布局中的第一个标签
     * @param labelSecond 水平布局中的第二个标签
     */
    void setKylinHBoxLayoutAttributes(QHBoxLayout *layout, QLabel *labelFirst, QLabel *labelSecond);
    /**
     * @brief setKylinHBoxLayoutAttributes 重载设置水平布局属性： 标签和组合框
     * @param layout 需要设置的水平布局
     * @param labelFirst 水平布局中的标签
     * @param combo 水平布局中的组合框
     */
    void setKylinHBoxLayoutAttributes(QHBoxLayout *layout, QLabel *labelFirst, KylinComboBox *combo);

private:
    QLabel *labDevice;              /**< 设备标签 */
    QLabel *labType;                /**< 类型标签 */
    QLabel *labColor;               /**< 色彩标签 */
    QLabel *labResalution;          /**< 分辨率标签 */
    QLabel *labSize;                /**< 尺寸标签 */
    QLabel *labFormat;              /**< 格式标签 */
    QLabel *labName;                /**< 名称标签 */
    QLabel *labLocation;            /**< 扫描至标签 */

    QFrame *line3;
    QFrame *line4;

    QPushButton *btnMail;         /**< 发送至邮件 */
    QPushButton *btnSave;         /**< 另存为 */
    QPushButton *btnLocation;    /**< 扫描至 */

    QLabel *textDevice;             /**< 设备 */
    QLabel *textType;               /**< 类型 */
    KylinComboBox *textColor;       /**< 色彩 */
    KylinComboBox *textResalution;  /**< 分辨率 */
    KylinComboBox *textSize;        /**< 尺寸 */
    KylinComboBox *textFormat;      /**< 格式 */
    QLabel *textName;               /**< 名称 */


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

private slots:
    void on_btnLocation_clicked();
};

#endif // SCAN_SET_H
