#ifndef MARK_DIALOG_H
#define MARK_DIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>


class mark_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit mark_dialog(QWidget *parent = nullptr);
    ~mark_dialog();
    QString get_lineedit();
private:
    QLabel *label;
    QLineEdit *lineedit;
    QFrame *line;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;


};

#endif // MARK_DIALOG_H
