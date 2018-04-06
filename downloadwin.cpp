#include "downloadwin.h"
#include "ui_downloadwin.h"
#include "QDir"
#include "QMessageBox"
#include "QFileDialog"
//#include "QList"

DownloadWin::DownloadWin(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::DownloadWin)
{     
    ui->setupUi(this);
    dw_info *dwi=new dw_info;
    dw_insert *dwinst=new dw_insert;
    //ui->dw_mdi->addSubWindow(dwi);
    ui->tabWidget->addTab(dwi, "Подробно");
    ui->tabWidget->addTab(dwinst, "Загрузка");
    connect(ui->pb_choice, SIGNAL(clicked()), SLOT(Choice()));
    connect(ui->pb_clear, SIGNAL(clicked()), ui->lw_download, SLOT(clear()));
    connect(ui->pb_clear, SIGNAL(clicked()), dwi, SLOT(clear()));
    connect(ui->pb_clear, SIGNAL(clicked()), dwinst, SLOT(clear()));
    connect(ui->lw_download, SIGNAL(itemClicked(QListWidgetItem*)), dwi, SLOT(itemCounting(QListWidgetItem*)));
    connect(dwi, SIGNAL(FileEmit(QFile*)), dwinst, SLOT(FileCounting(QFile*)));
}

//void DownloadWin::InsertSlot()
//{
//    QList <QListWidgetItem*> SelecItem=ui->lw_download->selectedItems();
//    QFile *photo=0;
//    QByteArray *phb=0;
//    QString *abbstr=0, *name=0, *suf=0;
//    foreach (QListWidgetItem *lw, SelecItem)
//    {
//        abbstr= new QString(lw->data(Qt::UserRole).toString());
//        photo = new QFile(*abbstr);
//        QFileInfo inf(*photo);
//        if (!photo->open(QIODevice::ReadOnly))
//        {
//            QMessageBox::critical(0,"Ошибка","Фотография "+inf.baseName()+" повреждена", QMessageBox::Ok);
//            continue;
//        }
//        name=new QString(inf.baseName());  //имя
//        phb=new QByteArray(photo->readAll());
//        *phb=qCompress(*phb, 5); //компресс
//        suf=new QString(inf.completeSuffix()); //формат
//        if (this->isEnabled())
//            this->setDisabled(true);
//        photo->close();
//        //dd= new DialogDownload(this, abbstr, name, suf, phb);
//        //dd->show();
//    }
//}

void DownloadWin::Choice()
{
    int count=Allitems.count();
    if (count>=20)
    {
        int i=QMessageBox::information(0, "Внимание", "Во избежание перегруженности окна загрузки"
                                                      "\nрекомендуется не загружать более 20 фотографий."
                                                      "\nЖелаете очистить остальные фотографии?",
                                                        QMessageBox::Yes, QMessageBox::No);
        if(i==QMessageBox::Yes)
        {
            ui->pb_clear->clicked(true);
        }
    }

    QListWidgetItem *pitem=0;
    QStringList lst=QFileDialog::getOpenFileNames(this, "Выберите один или несколько файлов",
                                      pst->value("/home","").toString(), "*.png *.jpeg *.jpg");
    if (!lst.empty())
    {
        QDir path(*lst.begin());
        pst->setValue("/home", path.absolutePath());
    }
    foreach(QString str, lst) {
        pitem = new QListWidgetItem(ui->lw_download);
        pitem->setIcon(QIcon(str));
        pitem->setData(Qt::UserRole, str);
        Allitems<<pitem;
    }
}

DownloadWin::~DownloadWin()
{
    delete ui;
}
