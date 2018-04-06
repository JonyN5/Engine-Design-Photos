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
    PgBr=new QProgressBar;
    PgBr->setRange(0, 100);
    PgBr->setMaximumWidth(200);
    PgBr->setAlignment(Qt::AlignCenter);
    PgBr->setStyle(QStyleFactory::create("Fusion"));
    statusBar()->addWidget(PgBr, 1);
    statusBar()->hide();
    connect(ui->action_auth, SIGNAL(triggered()), SLOT(OpenAuthorization()));
    connect(ui->action_ex, SIGNAL(triggered()), SLOT(close()));
    connect(ui->action_about, SIGNAL(triggered()), SLOT(OpenAbout()));
    connect(dw, SIGNAL(ShowProgBar(bool)), SLOT(ProgBar(bool)));
    connect(dw, SIGNAL(StepProgBar(int)), SLOT(ProgBarValue(int)));
    connect(dw, SIGNAL(setStatus(QString,int)), ui->statusbar, SLOT(showMessage(QString,int)));
    connect(dbv, SIGNAL(ShowPB(bool)), SLOT(ProgBar(bool)));
    connect(dbv, SIGNAL(StepPB(int)), SLOT(ProgBarValue(int)));
}

void EDPMain::OpenAuthorization()
{
    Authorization_menu *am=new Authorization_menu(0, false);
    am->show();
}

void EDPMain::OpenAbout()
{
    QMessageBox::about(this, "О программе", "EDP (Engine Design Photo) ver. 1.0"
                                            "\nданное сообщение дорабатывается");
}

void EDPMain::ProgBar(bool open)
{
    if (open)
        statusBar()->show();
    else
    {
        statusBar()->hide();
        PgBr->reset();
    }
}

void EDPMain::ProgBarValue(int step)
{
    PgBr->setValue(step);
}

EDPMain::~EDPMain()
{
    delete ui;
}
