#include "dw_info.h"
#include "ui_dw_info.h"

dw_info::dw_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dw_info)
{
    ui->setupUi(this);
}

void  dw_info::itemCounting(QListWidgetItem* item)
{
    QString str=item->data(Qt::UserRole).toString();
    QString numd, nums, w, h;
    QFile *photo = new QFile(str);
    if (photo->open(QIODevice::ReadOnly))
    {
        emit FileEmit(photo);
        QFileInfo inf(*photo);
        QPixmap lbPixmap(str);
        ui->lb_isize->setText(w.setNum(lbPixmap.size().width())+"x"+h.setNum(lbPixmap.size().height()));
        lbPixmap=lbPixmap.scaled(416, 312, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->lb_pix->setPixmap(lbPixmap);
        ui->lb_name->setText(inf.baseName());
        ui->lb_type->setText("Изображение "+inf.suffix());
        ui->lb_depth->setText(numd.setNum(lbPixmap.depth()));
        ui->lb_path->setText(str);
        ui->lb_crDate->setText(inf.birthTime().toString("dd.MM.yyyy hh:mm:ss"));
        ui->lb_chDate->setText(inf.lastModified().toString("dd.MM.yyyy hh:mm:ss"));
        ui->lb_size->setText(nums.setNum(static_cast<float>(inf.size())/1024/1024,'g',2)+" Mб");
    }
    photo->close();
}

void dw_info::clear()
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

dw_info::~dw_info()
{
    delete ui;
}
