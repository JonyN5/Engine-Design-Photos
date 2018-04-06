#ifndef DBVIEWWIN_H
#define DBVIEWWIN_H

#include "sqlconnect.h"
#include "dbv_info.h"
#include "QWidget"

namespace Ui {
class DBviewWin;
}

class DBviewWin : public QWidget
{
    Q_OBJECT
friend class Sqlconnect;
public:
    explicit DBviewWin(QWidget *parent = 0);
    ~DBviewWin();
public slots:
    void SelectSlot();
private:
    Ui::DBviewWin *ui;
};

#endif // DBVIEWWIN_H
