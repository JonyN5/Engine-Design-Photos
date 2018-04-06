#include "dbv_info.h"
#include "ui_dbv_info.h"

dbv_info::dbv_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dbv_info)
{
    ui->setupUi(this);
}

void  dbv_info::itemIndex(QModelIndex index)
{
    //QString sttr=index.data(Qt::UserRole).toString();
    QByteArray arr=index.data(Qt::UserRole).toByteArray();/*item->data(Qt::UserRole).toString();*/
    //QString numd, nums, w, h;
    QPixmap lbPixmap;
    //QFile *photo = new QFile(str);
    //if (photo->open(QIODevice::ReadOnly))
    if (lbPixmap.loadFromData(qUncompress(QByteArray::fromBase64(arr))))
    {
        //emit FileEmit(photo);
        //QFileInfo inf(*photo);

        //ui->lb_isize->setText(w.setNum(lbPixmap.size().width())+"x"+h.setNum(lbPixmap.size().height()));
        lbPixmap=lbPixmap.scaled(416, 312, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->lb_pix->setPixmap(lbPixmap);
//        ui->lb_name->setText(inf.baseName());
//        ui->lb_type->setText("Изображение "+inf.suffix());
//        ui->lb_depth->setText(numd.setNum(lbPixmap.depth()));
//        ui->lb_path->setText(str);
//        ui->lb_crDate->setText(inf.birthTime().toString("dd.MM.yyyy hh:mm:ss"));
//        ui->lb_chDate->setText(inf.lastModified().toString("dd.MM.yyyy hh:mm:ss"));
//        ui->lb_size->setText(nums.setNum(static_cast<float>(inf.size())/1024/1024,'g',2)+" Mб");
    }
//    else
//       ui->lb_pix->setText(sttr);
}

void dbv_info::clear()
{
    ui->lb_pix->clear();
    ui->lb_name->clear();
    ui->lb_type->clear();
    ui->lb_isize->clear();
    ui->lb_depth->clear();
    ui->lb_path->clear();
    ui->lb_crDate->clear();
    ui->lb_chDate->clear();
    ui->lb_size->clear();
}

dbv_info::~dbv_info()
{
    delete ui;
}
