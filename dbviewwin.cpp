#include "dbviewwin.h"
#include "ui_dbviewwin.h"

DBviewWin::DBviewWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBviewWin)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,0);
    ui->splitter->setStretchFactor(1,1);
    dbv_info *dbvi=new dbv_info;
    ui->tabWidget->addTab(dbvi, "Подробно");
    connect(ui->pb_GetBase, SIGNAL(clicked()), SLOT(SelectSlot()));
    connect(ui->tr_view, SIGNAL(clicked(QModelIndex)), dbvi, SLOT(itemIndex(QModelIndex)));
}

void DBviewWin::SelectSlot()
{
    ui->tr_view->setModel(SQLconnect::SelectQuery());
}

DBviewWin::~DBviewWin()
{
    delete ui;
}
