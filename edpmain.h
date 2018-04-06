#ifndef EDPMAIN_H
#define EDPMAIN_H

#include <QMainWindow>
#include "QStyle"
#include "QStyleFactory"
#include "QMdiArea"
#include "QMdiSubWindow"
#include "QProgressBar"
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
    void ProgBar(bool open);
    void ProgBarValue(int step);
    void OpenAbout();
    void OpenAuthorization();
private:
    Ui::EDPMain *ui;
    QMdiArea *pma;
    QProgressBar *PgBr;
};

#endif // EDPMAIN_H
