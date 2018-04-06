#ifndef NEW_COMBO_H
#define NEW_COMBO_H
#include "QWidget"
#include "QComboBox"
#include "QCheckBox"
#include "QRadioButton"
#include "QProcess"
#include "QLineEdit"
#include "setapp.h"
#include "sqlconnect.h"

class new_combo : public QComboBox
{
friend class SQLconnect;
public:
    explicit new_combo(QWidget *parent=0);
    void showPopup();
    void changeStat();
private slots:
    void readResult();
private:
    bool Nodes=false;
    QProcess getSQLNodes;
    QSettings *pst=SetApp::theApp()->settings();
    QWidget *parent_obj;
};

#endif // NEW_COMBO_H
