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
    connect(ui->cB_engine, SIGNAL(activated(int)), SLOT(SetFilterSelect(int)));
    connect(ui->cB_aggregate, SIGNAL(activated(int)), SLOT(SetFilterSelect(int)));
    QStringList sightList;
    sightList << "спереди" << "сверху" << "слева";
    ui->cB_sight->addItems(sightList);
    ui->rB_engine->setChecked(true);
    ui->cB_engine->addItems(SQLconnect::SelectName(1));
}

void dw_insert::setFK(int KEY)
{
    FKukey=KEY;
}

void dw_insert::SetFilterSelect(int NumItem)
{
    if (static_cast<QComboBox*>(sender())==ui->cB_engine)
    {
        setFK((SQLconnect::SelectKey(1)).at(NumItem+1));
        ui->cB_aggregate->addItems(SQLconnect::SelectName(2, FKukey));
    }
    if (static_cast<QComboBox*>(sender())==ui->cB_aggregate)
    {
        setFK((SQLconnect::SelectKey(2, FKukey)).at(NumItem+1));
        ui->cB_unit->addItems(SQLconnect::SelectName(3, FKukey));
    }
}

void dw_insert::FileCounting(QFile* Photo_file)
{
    photo=Photo_file;
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
    //по аналогии очищает..хотя..надо подумать
}

void dw_insert::on_pB_DownLoad_clicked()
{
    QByteArray *photoInByte=0;
    QString *suf=0, *byte64PhotoStr=0, BirthDate, ModifiedDate,
            Name, Sight;
    QFileInfo inf(*photo);
    if (photo->open(QIODevice::ReadOnly))
    {
        int tabl;
        if (ui->rB_engine->isChecked())
        {
           tabl=1;
           Name=ui->cB_engine->lineEdit()->text();
        }
        if (ui->rB_aggregate->isChecked())
        {
           tabl=2;
           Name=ui->cB_aggregate->lineEdit()->text();
        }
        if (ui->rB_unit->isChecked())
        {
           tabl=3;
           Name=ui->cB_unit->lineEdit()->text();
        }
        Sight=ui->cB_sight->currentText();
        photoInByte=new QByteArray(photo->readAll());
        *photoInByte=qCompress(*photoInByte, 5); //компресс
        byte64PhotoStr=new QString(photoInByte->toBase64()); //байтовой составл. фотогр. в виде текста
        suf=new QString(inf.completeSuffix()); //формат изображения
        BirthDate=inf.birthTime().toString("yyyyMMdd HH:mm:ss");
        ModifiedDate=inf.lastModified().toString("yyyyMMdd HH:mm:ss");
        SQLconnect::InsertQuery(FKukey, Name, byte64PhotoStr, suf, BirthDate, ModifiedDate, Sight, tabl);
    }
    photo->close();// проверить, закрывает ли указатель dw_info, и если да то наверное закрыть тут
}

dw_insert::~dw_insert()
{
    delete ui;
}


