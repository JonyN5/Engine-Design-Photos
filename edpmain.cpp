#include "edpmain.h"
#include "ui_edpmain.h"

EDPMain::EDPMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EDPMain)
{
    ui->setupUi(this);
    pma=new QMdiArea;  
    setCentralWidget(pma);
    DownloadWin *dw=new DownloadWin;
    QMdiSubWindow *dwsub=pma->addSubWindow(dw);
    dw->setWindowTitle("Загрузка");
    DBviewWin *dbv=new DBviewWin;
    pma->addSubWindow(dbv);
    dbv->setWindowTitle("Просмотр базы");
    pma->setActiveSubWindow(dwsub);
    pma->setViewMode(QMdiArea::TabbedView);
    connect(ui->action_auth, SIGNAL(triggered()), SLOT(OpenAuthorization()));
}

void EDPMain::OpenAuthorization()
{
    Authorization_menu *am=new Authorization_menu(0, false);
    am->show();
}

EDPMain::~EDPMain()
{
    delete ui;
}
