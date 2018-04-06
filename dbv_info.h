#ifndef dbv_info_H
#define dbv_info_H

#include <QWidget>
#include "QStandardItemModel"
#include "QModelIndex"
#include "QByteArray"
#include "QDateTime"
#include "QPixmap"
#include "QSize"

namespace Ui {
class dbv_info;
}

class dbv_info : public QWidget
{
    Q_OBJECT

public:
    explicit dbv_info(QWidget *parent = 0);
    ~dbv_info();
private slots:
    void clear();
    void itemIndex(QModelIndex index);
private:
    Ui::dbv_info *ui;
};

#endif // dbv_info_H
