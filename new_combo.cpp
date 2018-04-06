#include "new_combo.h"

new_combo::new_combo(QWidget *parent):
    QComboBox(parent)
{
    parent_obj=parent;
    connect(&getSQLNodes,&QProcess::readyRead, this, &new_combo::readResult);
}

void new_combo::showPopup()
{
    if (this->objectName()=="cB_engine")
    {
        this->clear();
        if(!(parent_obj->findChild<QCheckBox*>("chB")->isChecked() &&
           parent_obj->findChild<QRadioButton*>("rB_engine")->isChecked()))
        {
            this->addItems(SQLconnect::SelectName(1));
            QComboBox::showPopup();
        }
    }
    if (this->objectName()=="cB_aggregate")
    {
        this->clear();
        if(!(parent_obj->findChild<QCheckBox*>("chB")->isChecked() &&
             parent_obj->findChild<QRadioButton*>("rB_aggregate")->isChecked()))
        {
             int NumItem=parent_obj->findChild<QComboBox*>("cB_engine")->currentIndex();
             this->addItems(SQLconnect::SelectName(2, NumItem+1));
             QComboBox::showPopup();
        }
    }
    if (this->objectName()=="cB_unit")
    {
        this->clear();
        if(!(parent_obj->findChild<QCheckBox*>("chB")->isChecked() &&
                parent_obj->findChild<QRadioButton*>("rB_unit")->isChecked()))
        {
            int NumItem=parent_obj->findChild<QComboBox*>("cB_aggregate")->currentIndex();
            this->addItems(SQLconnect::SelectName(3, NumItem+1));
            QComboBox::showPopup();
        }
    }
    if (this->objectName()=="cB_server")
    {
        getSQLNodes.setProgram("SQLCMD");
        getSQLNodes.setArguments({"-Lc"});
        getSQLNodes.start();
    }  
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
