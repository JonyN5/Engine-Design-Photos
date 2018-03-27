#include "authorization_menu.h"
#include "ui_authorization_menu.h"
//#include "QTimer"

Authorization_menu::Authorization_menu(QWidget *parent, bool st) :
    QDialog(parent),
    status(st),
    ui(new Ui::Authorization_menu)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setFixedSize(this->size());
    ui->le_pass->setEchoMode(QLineEdit::Password);
    this->readDrivers();
    ui->le_login->setText(pst->value("/login","").toString());
    ui->cB_server->lineEdit()->setText(pst->value("/server","").toString());
    ui->cB_driver->lineEdit()->setText(pst->value("/driver","").toString());
}

Authorization_menu::~Authorization_menu()
{
    delete ui;
}

void Authorization_menu::readDrivers()
{
    int i=1;
    QString Dr_name;
    QRegExp rexp("ODBC|SQL");
    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\ODBC\\ODBCINST.INI\\ODBC Drivers", QSettings::NativeFormat);
    QStringList drlist=reg.allKeys();
    foreach (Dr_name, drlist) {
        if (Dr_name.contains(rexp))
        {
            ui->cB_driver->setCurrentIndex(i);
            ui->cB_driver->addItem(Dr_name);
            i++;
        }
    }
    ui->cB_driver->lineEdit()->setText(pst->value("/driver","").toString());
}

void Authorization_menu::on_pb_join_clicked()
{
    SQLconnect sq("TestBaza", ui->le_login->text(), ui->cB_server->lineEdit()->text(), ui->le_pass->text(),
                  ui->cB_driver->lineEdit()->text());
    QPalette pal=ui->lab_stat->palette();
    ui->le_pass->clear();
    if (sq.createConnection()) /*(true)*/
    {
       ui->lab_stat->setText("Доступ разрешён");
       //pal.setColor(QPalette::WindowText, Qt::green); //задаёт цвет
       //QTimer time;
       //time.start(100000);
       pst->setValue("/server",ui->cB_server->lineEdit()->text());
       pst->setValue("/driver",ui->cB_driver->lineEdit()->text());
       pst->setValue("/login",ui->le_login->text());
       this->close();
       if (status)
       {
            EDPMain *em=new EDPMain;
            em->show();
       }
    }
    else
    {
       ui->lab_stat->setText("Доступ запрещён");
       pal.setColor(QPalette::WindowText, Qt::red); //QPalette::WindowText или QPalette::Foreground (различия неизвестны)
    }
    ui->lab_stat->setPalette(pal); //устанавливает палитру
}
