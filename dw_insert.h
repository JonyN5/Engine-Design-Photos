#ifndef DW_INSERT_H
#define DW_INSERT_H

#include <QWidget>
#include "QListWidgetItem"

namespace Ui {
class dw_insert;
}

class dw_insert : public QWidget
{
    Q_OBJECT

public:
    explicit dw_insert(QWidget *parent = 0);
    ~dw_insert();
private slots:
    void clear();
    void itemCounting(QListWidgetItem* item);
    void on_pB_DownLoad_clicked();
private:
    Ui::dw_insert *ui;
};

#endif // DW_INSERT_H
