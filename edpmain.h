#ifndef EDPMAIN_H
#define EDPMAIN_H

#include <QMainWindow>
#include "QMdiArea"
#include "QMdiSubWindow"
#include "authorization_menu.h"
#include "dbviewwin.h"
#include "downloadwin.h"

namespace Ui {
class EDPMain;
}

class EDPMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit EDPMain(QWidget *parent = 0);
    ~EDPMain();
private slots:
    void OpenAuthorization();
private:
    Ui::EDPMain *ui;
    QMdiArea *pma;
};

#endif // EDPMAIN_H
