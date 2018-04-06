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
    QByteArray arr=index.data(Qt::UserRole).toByteArray();
    QString name=index.data().toString();
    QPixmap lbPixmap;
    if (arr!="")
    {
        if (lbPixmap.loadFromData(qUncompress(QByteArray::fromBase64(arr))))
        {
            lbPixmap=lbPixmap.scaled(416, 312, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->lb_pix->setPixmap(lbPixmap);
            ui->lb_name->setText(name);
        }
    }
}

dbv_info::~dbv_info()
{
    delete ui;
}
