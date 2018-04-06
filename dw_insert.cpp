#include "dw_insert.h"
#include "ui_dw_insert.h"

dw_insert::dw_insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dw_insert)
{
    ui->setupUi(this);
    connect(ui->rB_engine, SIGNAL(toggled(bool)), SLOT(reactToToggl(bool)));
    connect(ui->rB_aggregate, SIGNAL(toggled(bool)), SLOT(reactToToggl(bool)));
    connect(ui->rB_unit, SIGNAL(toggled(bool)), SLOT(reactToToggl(bool)));
    connect(ui->chB, SIGNAL(stateChanged(int)), SLOT(ClearListCombo(int)));
    //connect(ui->cB_engine, SIGNAL(activated(int)), SLOT(SetFilterSelect(int)));
    //connect(ui->cB_aggregate, SIGNAL(activated(int)), SLOT(SetFilterSelect(int)));
    QStringList sightList;
    sightList << "спереди" << "сверху" << "слева";
    ui->cB_sight->addItems(sightList);
    ui->rB_engine->setChecked(true);
    //ui->cB_engine->addItems(SQLconnect::SelectName(1));
    ui->cB_engine->lineEdit()->setText("");
    //emit emitCombo(ui->cB_engine);
}

//void dw_insert::setFK(int tabl, int KEY)
//{
//    switch (tabl)
//    {
//        case 2: FKEukey=KEY; break;
//        case 3: FKAukey=KEY; break;
//    }
//}

//void dw_insert::SetFilterSelect(int NumItem)
//{
//    if (static_cast<QComboBox*>(sender())==ui->cB_engine)
//    {
//        setFK(2, SQLconnect::SelectKey(1).at(NumItem));
//        if (ui->cB_aggregate->count()!=0)
//            ui->cB_aggregate->clear();
//        ui->cB_aggregate->addItems(SQLconnect::SelectName(2, FKEukey));
//        if (ui->cB_aggregate->isEditable())
//            ui->cB_aggregate->lineEdit()->setText("");
//    }
//    if (static_cast<QComboBox*>(sender())==ui->cB_aggregate)
//    {
//        setFK(3, SQLconnect::SelectKey(2, FKEukey).at(NumItem));
//        if (ui->cB_unit->count()!=0)
//            ui->cB_unit->clear();
//        ui->cB_unit->addItems(SQLconnect::SelectName(3, FKAukey));
//        if (ui->cB_unit->isEditable())
//            ui->cB_unit->lineEdit()->setText("");
//    }
//}

void dw_insert::ClearListCombo(int state)
{
    if (state)
    {
        if (ui->rB_engine->isChecked())
        {
           ui->cB_engine->clear();
        }
        if (ui->rB_aggregate->isChecked())
        {
           ui->cB_aggregate->clear();
        }
        if (ui->rB_unit->isChecked())
        {
           ui->cB_unit->clear();
        }
    }

}

void dw_insert::FileCounting(QFile* Photo_file)
{
    photo=Photo_file;
}

void dw_insert::ItemCounting(QListWidgetItem *Photo_item)
{
    item=Photo_item;
}

void dw_insert::reactToToggl(bool check)
{
    if (static_cast<QRadioButton*>(sender())==ui->rB_engine && check)
    {
        ui->lb_engine->show();
        ui->lb_aggregate->hide();
        ui->lb_unit->hide();
        ui->cB_engine->show();
        ui->cB_engine->setEditable(true);
        ui->cB_aggregate->hide();
        ui->cB_unit->hide();
    }
    if (static_cast<QRadioButton*>(sender())==ui->rB_aggregate && check)
    {
        ui->lb_engine->show();
        ui->lb_aggregate->show();
        ui->lb_unit->hide();
        ui->cB_engine->show();
        ui->cB_engine->setEditable(false);
        ui->cB_aggregate->show();
        ui->cB_aggregate->setEditable(true);
        ui->cB_unit->hide();
    }
    if (static_cast<QRadioButton*>(sender())==ui->rB_unit && check)
    {
        ui->lb_engine->show();
        ui->lb_aggregate->show();
        ui->lb_unit->show();
        ui->cB_engine->show();
        ui->cB_engine->setEditable(false);
        ui->cB_aggregate->show();
        ui->cB_aggregate->setEditable(false);
        ui->cB_unit->show();
    }
}

void dw_insert::clear()
{   
    ui->rB_engine->toggle();
    ui->cB_engine->lineEdit()->setText("");
}

void dw_insert::on_pB_DownLoad_clicked()
{
    QByteArray *photoInByte=0;
    QString *suf=0, *byte64PhotoStr=0, BirthDate, ModifiedDate,
            Name, Sight;
    int KeyI, UkeyI=0, NumItemEng, NumItemAgr, NumItemUn;
    QFileInfo inf(*photo);
    emit ShowProgBar(true);
    emit setStatus("Загрузка "+inf.baseName()+"...", 10);
    if (photo->open(QIODevice::ReadOnly))
    {
        int tabl;
        if (ui->rB_engine->isChecked())
        {
           tabl=1;
           Name=ui->cB_engine->lineEdit()->text();
           NumItemEng=ui->cB_engine->currentIndex()+1;
           if (NumItemEng!=0)
               UkeyI=NumItemEng;
           KeyI=0;
        }
        if (ui->rB_aggregate->isChecked())
        {
           tabl=2;
           Name=ui->cB_aggregate->lineEdit()->text();
           NumItemEng=ui->cB_engine->currentIndex()+1;
           NumItemAgr=ui->cB_aggregate->currentIndex()+1;
           if (NumItemAgr!=0)
               UkeyI=NumItemAgr;
           KeyI=NumItemEng;
                   //SQLconnect::SelectKey(1, NumItemEng).at(NumItemAgr);
        }
        if (ui->rB_unit->isChecked())
        {
           tabl=3;
           Name=ui->cB_unit->lineEdit()->text();
           NumItemAgr=ui->cB_aggregate->currentIndex()+1;
           NumItemUn=ui->cB_unit->currentIndex()+1;
           if (NumItemUn!=0)
               UkeyI=NumItemUn;
           KeyI=NumItemAgr;
           //SQLconnect::SelectKey(2, NumItemAgr).at(NumItemUn);
        }
        Sight=ui->cB_sight->currentText();
        photoInByte=new QByteArray(photo->readAll());
        *photoInByte=qCompress(*photoInByte, 5); //компресс
        byte64PhotoStr=new QString(photoInByte->toBase64()); //байтовой составл. фотогр. в виде текста
        suf=new QString(inf.completeSuffix()); //формат изображения
        BirthDate=inf.birthTime().toString("yyyyMMdd HH:mm:ss");
        ModifiedDate=inf.lastModified().toString("yyyyMMdd HH:mm:ss");
        if(SQLconnect::InsertQuery(KeyI, Name, byte64PhotoStr, suf, BirthDate, ModifiedDate, Sight, tabl, UkeyI))
        {
           emit setStatus(Name+" загружена в базу", 15000);
           item->setBackgroundColor(QColor(0, 255, 0));
        }
    }
    photo->close();// проверить, закрывает ли указатель dw_info, и если да то наверное закрыть тут
}

dw_insert::~dw_insert()
{
    delete ui;
}


