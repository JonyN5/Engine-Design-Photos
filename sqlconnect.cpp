#include "sqlconnect.h"
#include "QMessageBox"
//#include "probar.h"

SQLconnect::SQLconnect(QString DB, QString User, QString Host, QString Pass, QString Driver)
{
    DBName=DB;
    UserName=User;
    HostName=Host;
    Password=Pass;
    DrivName=Driver;
}

bool SQLconnect::createConnection()
{
   QString dbstr="Driver={"+DrivName+"}; "
   "Server="+HostName+"; Database="+DBName+"; Uid="+UserName+"; "
   "Pwd="+Password+";"; //Trusted_Connection=yes;
   if (QSqlDatabase::contains("first"))
   {
       db = QSqlDatabase::addDatabase("QODBC", "second");
       db.setDatabaseName(dbstr);
       if (!db.open())
       {
               QMessageBox::critical(0, "Unable to open database", "An error occurred while "
                                          "opening the connection: " + db.lastError().text());
               QMessageBox::warning(0, "Ошибка входа", "Неверный пользователь. Проверьте логин, пароль а тажке имя (ip) хоста к которому подключаетесь", QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
           return false;
       }
       //if (QSqlDatabase::contains("first"))
       QSqlDatabase::removeDatabase("first");
       return true;
   }
   else
       db = QSqlDatabase::addDatabase("QODBC", "first");
       db.setDatabaseName(dbstr);
       if (!db.open())
       {
               QMessageBox::critical(0, "Unable to open database", "An error occurred while "
                                        "opening the connection: " + db.lastError().text());
               QMessageBox::warning(0, "Ошибка входа", "Неверный пользователь. Проверьте логин, пароль а тажке имя (ip) хоста к которому подключаетесь", QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
             return false;
       }
       if (QSqlDatabase::contains("second"))
           QSqlDatabase::removeDatabase("second");
       return true;
}

void SQLconnect::InsertQuery(QString *Name, QString *bt64, QString *suf)
{
    QString str, strf;
    QSqlQuery query(QSqlDatabase::database(QSqlDatabase::contains("first") ? "first" : "second"));
    strf="INSERT INTO [TestBaza].[dbo].[Photo] (Название, Изображение, Формат) "
         "VALUES('%1', '%2', '%3')";
    str=strf.arg(*Name).arg(*bt64).arg(*suf);
    query.exec(str);
    if (query.lastError().type() != QSqlError::NoError)
      QMessageBox::warning(0, "Ошибка загрузки", "Не удалось загрузить по следующим причинам: " + query.lastError().text());
}

void SQLconnect::SelectQuery(QTreeWidget *lv)
{
    //ProBar *pgr=new ProBar;
    QTreeWidgetItem *pitem=0;
    QStringList lst;
    lst<<"Название";
    lv->setHeaderHidden(false);
    lv->setHeaderLabels(lst);
    QPixmap img;
    QString str;
    QByteArray arr;
    QSqlQuery query(QSqlDatabase::database(QSqlDatabase::contains("first") ? "first" : "second"));
    query.exec("Select * FROM [TestBaza].[dbo].[Photo]");
    QSqlRecord rec=query.record();
    //pgr->Step(0);
    //int r=query.numRowsAffected();
    //int c=100/r+1, i=1;
    while (query.next())
    {
        pitem = new QTreeWidgetItem(lv);
        arr=query.value(rec.indexOf("Изображение")).toByteArray();
        str=query.value(rec.indexOf("Название")).toString();
        pitem->setText(0, str);
        if (img.loadFromData(QByteArray::fromBase64(arr)))
           pitem->setIcon(0, QPixmap(img));
        //pgr->Step(i*c);
        //i++;
        //qApp->processEvents();
    }
    //pgr->Step(100);
    //pgr->close();
}
