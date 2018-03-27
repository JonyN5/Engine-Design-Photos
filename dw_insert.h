#ifndef DW_INSERT_H
#define DW_INSERT_H

#include <QWidget>
#include "QListWidgetItem"
#include "QLineEdit"
#include "QFileInfoList"
#include "QFile"
#include "QDateTime"
#include "sqlconnect.h"

namespace Ui {
class dw_insert;
}

class dw_insert : public QWidget
{
    Q_OBJECT
friend class SQLconnect;
public:
    explicit dw_insert(QWidget* parent = 0);
    ~dw_insert();

private slots:
    void clear();
    void FileCounting(QFile* Photo_file);
    void SetFilterSelect(int NumItem);
    void reactToToggl(bool check);
    void on_pB_DownLoad_clicked();
private:
    void setFK(int KEY); //устанавливает значения для FK
    QFile *photo;
    int FKukey;
    Ui::dw_insert *ui;
};

#endif // DW_INSERT_H
