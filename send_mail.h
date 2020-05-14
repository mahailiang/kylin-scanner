#ifndef SEND_MAIL_H
#define SEND_MAIL_H
#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QFrame>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QProcess>

#ifdef signals
#undef signals
#endif
extern "C" {
#include <glib.h>
#include <gio/gio.h>
#include <gio/gdesktopappinfo.h>
}
#define MAILTYPE "x-scheme-handler/mailto"
#define DESKTOPPATH "/usr/share/applications/"
typedef struct _Applist
{
    char *appid;
}AppList;//用于存放应用列表

typedef struct _AppInfo
{
    GAppInfo *item;
}Appinfo;//用于存放应用列表信息
class no_mail : public QDialog
{
    Q_OBJECT
public:
    explicit no_mail(QWidget *parent = nullptr);
    ~no_mail();
private:
    QLabel *labTitle;
    QTextEdit *textEdit;
    QFrame *line;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;


};

class send_mail : public QDialog
{
    Q_OBJECT
public:
    explicit send_mail(QWidget *parent = nullptr);
    void set_btnList();
    void open_email(QString name);

private:
    QLabel *labTitle;
    QPushButton *btnCancel;
    QHBoxLayout *hBoxLayout;
    QHBoxLayout *hBoxLayout1;
    QVBoxLayout *vBoxLayout;
    QVBoxLayout *vBoxLayout1;
    QScrollArea *scrollArea;
    QWidget *widget;
    QList<QPushButton *> btnList;
    QList<QString> desktopName;

private slots:
    void on_btn_clicked(void);

};
Appinfo * _getAppList(const char *contentType);
AppList * getAppIdList(const char *contentType);
#endif // MARK_DIALOG_H
