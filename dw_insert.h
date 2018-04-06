#ifndef DW_INSERT_H
#define DW_INSERT_H

#include <QWidget>
#include "QListWidgetItem"
#include "QLineEdit"
#include "QFileInfoList"
#include "QFile"
#include "QDateTime"
#include "sqlconnect.h"
#include "new_combo.h"

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
signals:
    void setStatus(QString, int);
    void ShowProgBar(bool);
private slots:
    void clear();
    void FileCounting(QFile* Photo_file);
    void ItemCounting(QListWidgetItem* Photo_item);
    void ClearListCombo(int state);
    //void SetFilterSelect(int NumItem);
    void reactToToggl(bool check);
    void on_pB_DownLoad_clicked();
private:
    //void setFK(int tabl, int KEY); //устанавливает значения для FK
    QFile *photo;
    QListWidgetItem* item;
    //int FKEukey, FKAukey;
    Ui::dw_insert *ui;
};

#endif // DW_INSERT_H
