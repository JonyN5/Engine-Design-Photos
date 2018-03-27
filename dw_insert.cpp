#include "dw_insert.h"
#include "ui_dw_insert.h"

dw_insert::dw_insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dw_insert)
{
    ui->setupUi(this);
}

void dw_insert::itemCounting(QListWidgetItem* item)
{

}

void dw_insert::clear()
{
    //по аналогии очищает..хотя..надо подумать
}

void dw_insert::on_pB_DownLoad_clicked()
{
    //сама загрузка в sqlconnect
}

dw_insert::~dw_insert()
{
    delete ui;
}


