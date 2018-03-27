#include "sqlconnect.h"
#include "QMessageBox"
//#include "probar.h"

SQLconnect::SQLconnect(QString DB,
                       QString User,
                       QString Host,
                       QString Pass,
                       QString Driver)
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
   {
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
}

void SQLconnect::InsertQuery(int FK,
                             QString Name,
                             QString *Bt64str,
                             QString *suf,
                             QString BirthD,
                             QString ModifiedD,
                             QString SightCh,
                             int tabl)
{
    QString str, strf;
    QSqlQuery query(QSqlDatabase::database(QSqlDatabase::contains("first") ? "first" : "second"));
    switch (tabl)
    {
    case 1:
        strf="INSERT INTO [TestBaza].[dbo].[Двигатели] (UKEY, Название, Изображение, Тип, "
             "Дата создания, Дата модификации, Дата записи, Вид) "
             "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')";

        str=strf.arg(SQLconnect::countRecords(1)+1);
        break;

    case 2:
        strf="INSERT INTO [TestBaza].[dbo].[Агрегаты] (EngUKEY, UKEY, Название, Изображение, Тип, "
             "Дата создания, Дата модификации, Дата записи, Вид) "
             "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')";

        str=strf.arg(FK).arg(SQLconnect::countRecords(1)+SQLconnect::countRecords(2)+1);
        break;

    case 3:
        strf="INSERT INTO [TestBaza].[dbo].[Элементы] (AgrUKEY, UKEY, Название, Изображение, Тип, "
             "Дата создания, Дата модификации, Дата записи, Вид) "
             "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')";

        str=strf.arg(FK).arg(SQLconnect::countRecords(1)+SQLconnect::countRecords(2)+SQLconnect::countRecords(3)+1);
        break;
    }
    str=strf.arg(Name)
            .arg(*Bt64str)
            .arg(*suf)
            .arg(BirthD)
            .arg(ModifiedD)
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss"))
            .arg(SightCh);

    query.exec(str);
    if (query.lastError().type() != QSqlError::NoError)
      QMessageBox::warning(0, "Ошибка загрузки", "Не удалось загрузить по следующим причинам: " + query.lastError().text());
}

int SQLconnect::countRecords(int tabl)
{
    QSqlRecord rec;
    QSqlQuery query(QSqlDatabase::database(QSqlDatabase::contains("first") ? "first" : "second"));
    switch (tabl)
    {
    case 1:
        query.exec("Select Ukey FROM [TestBaza].[dbo].[Двигатели]");
        break;
    case 2:
        query.exec("Select Ukey FROM [TestBaza].[dbo].[Агрегаты]");
        break;
    case 3:
        query.exec("Select Ukey FROM [TestBaza].[dbo].[Элементы]");
        break;
    default: query.exec();
    }
    rec=query.record();
    return rec.count();
}

QList <int> SQLconnect::SelectKey(int tabl, int FK)
{ 
   int ukey;
   QSqlRecord rec;
   QList <int> PKE, PKA, PKU, Null;
   QSqlQuery query(QSqlDatabase::database(QSqlDatabase::contains("first") ? "first" : "second"));
   query.exec("Select UKEY FROM [TestBaza].[dbo].[Двигатели]");
   switch (tabl)
   {
       case 1: query.exec("Select UKEY FROM [TestBaza].[dbo].[Двигатели]");
       rec=query.record();
       while (query.next())
       {
          ukey=query.value(rec.indexOf("UKEY")).toInt();
          PKE<<ukey;
       }
       return PKE;
       break;

       case 2: query.exec("Select UKEY FROM [TestBaza].[dbo].[Агрегаты]"
                          "Where EngUKEY="+FK);
       rec=query.record();
       while (query.next())
       {
          ukey=query.value(rec.indexOf("UKEY")).toInt();
          PKA<<ukey;
       }
       return PKA;
       break;

       case 3: query.exec("Select UKEY FROM [TestBaza].[dbo].[Элементы]"
                          "Where AgrUKEY="+FK);
       rec=query.record();
       while (query.next())
       {
          ukey=query.value(rec.indexOf("UKEY")).toInt();
          PKU<<ukey;
       }
       return PKU;
       break;

       default: return Null;
   }
}

QStringList SQLconnect::SelectName(int tabl, int FK)
{
    QString name;
    QSqlRecord rec;
    QList <QString> NameEng, NameAgr, NameUn, Null;
    QSqlQuery query(QSqlDatabase::database(QSqlDatabase::contains("first") ? "first" : "second"));
    switch (tabl)
    {
        case 1: query.exec("Select Название FROM [TestBaza].[dbo].[Двигатели]");
        rec=query.record();
        while (query.next())
        {
           name=query.value(rec.indexOf("Название")).toString();
           NameEng<<name;
        }
        return NameEng;
        break;

        case 2: query.exec("Select Название FROM [TestBaza].[dbo].[Агрегаты]"
                           "Where EngUKEY="+FK);
        rec=query.record();
        while (query.next())
        {
           name=query.value(rec.indexOf("Название")).toString();
           NameAgr<<name;
        }
        return NameAgr;
        break;

        case 3: query.exec("Select Название FROM [TestBaza].[dbo].[Элементы]"
                           "Where AgrUKEY="+FK);
        rec=query.record();
        while (query.next())
        {
           name=query.value(rec.indexOf("Название")).toString();
           NameUn<<name;
        }
        return NameUn;
        break;

        default: return Null;
    }

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
