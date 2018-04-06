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
    sq=new SQLconnect;
    ui->tabWidget->addTab(dbvi, "Подробно");
    connect(ui->pb_GetBase, SIGNAL(clicked()), SLOT(SelectSlot()));
    connect(ui->tr_view, SIGNAL(clicked(QModelIndex)), dbvi, SLOT(itemIndex(QModelIndex)));
    connect(sq, SIGNAL(ShowProgBar(bool)), SIGNAL(ShowPB(bool)));
    connect(sq, SIGNAL(StepProgBar(int)), SIGNAL(StepPB(int)));
}

void DBviewWin::SelectSlot()
{
    ui->tr_view->setModel(sq->SelectQuery());
}

DBviewWin::~DBviewWin()
{
    delete ui;
}
