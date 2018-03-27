#include "dbviewwin.h"
#include "ui_dbviewwin.h"

DBviewWin::DBviewWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBviewWin)
{
    ui->setupUi(this);
    ui->lw_view->isHeaderHidden();
    connect(ui->pb_GetBase, SIGNAL(clicked()), SLOT(SelectSlot()));
}

void DBviewWin::SelectSlot()
{
    SQLconnect::SelectQuery(ui->lw_view);
}

DBviewWin::~DBviewWin()
{
    delete ui;
}
