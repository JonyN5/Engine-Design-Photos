#ifndef DW_INFO_H
#define DW_INFO_H

#include <QWidget>
#include "QListWidgetItem"
#include "QFileInfoList"
#include "QFile"
#include "QDateTime"
#include "QPixmap"
#include "QSize"

namespace Ui {
class dw_info;
}

class dw_info : public QWidget
{
    Q_OBJECT

public:
    explicit dw_info(QWidget *parent = 0);
    ~dw_info();
private slots:
    void clear();
    void itemCounting(QListWidgetItem* item);
private:
    Ui::dw_info *ui;
};

#endif // DW_INFO_H
