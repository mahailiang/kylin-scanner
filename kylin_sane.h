#ifndef KYLIN_SANE_H
#define KYLIN_SANE_H

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QStringList>

#include "sane/sane.h"
#include "sane/saneopts.h"

#include <iostream>
using namespace std;

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

struct device_info
{
    bool status;			//是否存在设备，存在status值为true，否则为false
    QString name;			//设备名
    QString type;			//设备类型
    QStringList color;		//设备支持的色彩
    QStringList resolution;	//设备支持的分辨率
    QStringList size; 		//设备支持的尺寸
};

struct user_selected_info
{
    QString color;
    QString resolution;
    QString size;
};

enum sizes_type
{
    A2 = 1,
    A3,
    A4,
    A5,
    A6
};

class  KylinSane: public QWidget
{
    Q_OBJECT
public:
    explicit KylinSane(QWidget *parent = nullptr);
    ~KylinSane();
    KylinSane(const KylinSane &) = delete ;
    KylinSane &operator = (const KylinSane &) = delete ;

    static KylinSane& getInstance()
    {
        static KylinSane instance; //局部静态变量
        return instance;
    }

    bool getKylinSaneStatus();
    QString getKylinSaneName();
    QString getKylinSaneType();
    QStringList getKylinSaneResolutions();
    QStringList getKylinSaneSizes();
    QStringList getKylinSaneColors();

    void setKylinSaneStatus(bool status);
    void setKylinSaneName(QString name);
    void setKylinSaneType(QString type);
    void setKylinSaneResolutions(QStringList resolution);
    void setKylinSaneSizes(QStringList size);
    void setKylinSaneColors(QStringList color);

    device_info open_device();
    int start_scanning(user_selected_info info);

    SANE_Handle handle;
    struct user_selected_info userInfo;

private:
    struct device_info devicesInfo;

public slots:
};


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize SANE
 **/
void init();
// Get all devices
SANE_Status get_devices(const SANE_Device ***device_list);
// Open a device
SANE_Status open_sane_device(SANE_Device *device, SANE_Handle *sane_handle);
// Start scanning
SANE_Status start_scan(SANE_Handle sane_handle, SANE_String_Const fileName);
// Cancel scanning
void cancle_scan(SANE_Handle sane_handle);
// Close SANE device
void close_device(SANE_Handle sane_handle);
// Release SANE resources
void my_sane_exit();

char *kylin_display_scan_parameters(SANE_Handle device);
void kylinNorScanOpen();


#ifdef __cplusplus
}
#endif

#endif
