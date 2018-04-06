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
public:
    explicit DBviewWin(QWidget *parent = 0);
    ~DBviewWin();
signals:
   void ShowPB(bool);
   void StepPB(int);
public slots:
    void SelectSlot();
private:
    Ui::DBviewWin *ui;
    SQLconnect *sq;
};

#endif // DBVIEWWIN_H
