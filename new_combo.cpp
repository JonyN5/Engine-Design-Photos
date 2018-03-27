#include "new_combo.h"

new_combo::new_combo(QWidget *parent):
    QComboBox(parent)
{
    connect(&getSQLNodes,&QProcess::readyRead, this, &new_combo::readResult);
}

void new_combo::showPopup()
{
    getSQLNodes.setProgram("SQLCMD");
    getSQLNodes.setArguments({"-Lc"});
    getSQLNodes.start();
}

void new_combo::changeStat()
{
    Nodes=true;
}

void new_combo::readResult()
{
    if (!Nodes)
    {
        this->changeStat();
        int i=1;
        while(getSQLNodes.bytesAvailable()){
            QString DSNservers = getSQLNodes.readLine();
            DSNservers.chop(2);
            this->setCurrentIndex(i);
            this->addItem(DSNservers);
            i++;
        }
    }
    this->lineEdit()->setText(pst->value("/server","").toString());
    QComboBox::showPopup();
}
