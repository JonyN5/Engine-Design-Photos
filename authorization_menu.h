#ifndef AUTHORIZATION_MENU_H
#define AUTHORIZATION_MENU_H

#include <QDialog>
#include "sqlconnect.h"
#include "setapp.h"
#include "edpmain.h"
#include "QPalette"

namespace Ui {
class Authorization_menu;
}

class Authorization_menu : public QDialog
{
    Q_OBJECT
friend class Sqlconnect;
public:
    explicit Authorization_menu(QWidget *parent = 0, bool st=true);
    ~Authorization_menu();
    void readDrivers();
public slots:
    void on_pb_join_clicked();
private:
    bool status; //для отслеживания нужно ли открывать EDPmain объект
    Ui::Authorization_menu *ui;
    QSettings *pst=SetApp::theApp()->settings();
};

#endif // AUTHORIZATION_MENU_H
