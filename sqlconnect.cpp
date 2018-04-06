#include "sqlconnect.h"
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
             "[Дата создания], [Дата модификации], [Дата записи], Вид) "
             "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')";

        strf=strf.arg(SQLconnect::countRecords(1)+1);
        break;

    case 2:
        strf="INSERT INTO [TestBaza].[dbo].[Агрегаты] (EngUKEY, UKEY, Название, Изображение, Тип, "
             "[Дата создания], [Дата модификации], [Дата записи], Вид) "
             "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')";

        strf=strf.arg(FK).arg(SQLconnect::countRecords(1)+SQLconnect::countRecords(2)+1);
        break;

    case 3:
        strf="INSERT INTO [TestBaza].[dbo].[Элементы] (AgrUKEY, UKEY, Название, Изображение, Тип, "
             "[Дата создания], [Дата модификации], [Дата записи], Вид) "
             "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')";

        strf=strf.arg(FK).arg(SQLconnect::countRecords(1)+SQLconnect::countRecords(2)+SQLconnect::countRecords(3)+1);
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
    return query.numRowsAffected();
}

QList <int> SQLconnect::SelectKey(int tabl, int FK)
{ 
   int ukey;
   QSqlRecord rec;
   QString key;
   key.setNum(FK);
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
                          "Where EngUKEY='"+key+"'");
       rec=query.record();
       while (query.next())
       {
          ukey=query.value(rec.indexOf("UKEY")).toInt();
          PKA<<ukey;
       }
       return PKA;
       break;

       case 3: query.exec("Select UKEY FROM [TestBaza].[dbo].[Элементы]"
                          "Where AgrUKEY='"+key+"'");
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
    QString name, key;
    key.setNum(FK);
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
                           "Where EngUKEY='"+key+"'");
        rec=query.record();
        while (query.next())
        {
           name=query.value(rec.indexOf("Название")).toString();
           NameAgr<<name;
        }
        return NameAgr;
        break;

        case 3: query.exec("Select Название FROM [TestBaza].[dbo].[Элементы]"
                           "Where AgrUKEY='"+key+"'");
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

QStandardItemModel *SQLconnect::SelectQuery()
{
    QSqlDatabase vdb=QSqlDatabase::database(QSqlDatabase::contains("first") ? "first" : "second");
    QSqlQuery queryEng(vdb), queryAgr(vdb), queryUn(vdb);
    queryEng.exec("Select UKEY, Название, Изображение, [Дата записи], Вид FROM [TestBaza].[dbo].[Двигатели]");
    queryAgr.prepare("Select UKEY, Название, Изображение, [Дата записи], Вид FROM [TestBaza].[dbo].[Агрегаты]"
                     "Where EngUKEY=:KEY");
    queryUn.prepare("Select Название, Изображение, [Дата записи], Вид FROM [TestBaza].[dbo].[Элементы]"
                    "Where AgrUKEY=:KEY");
    QSqlRecord recEng=queryEng.record(), recAgr, recUn;
    QStandardItemModel *model=new QStandardItemModel(queryEng.numRowsAffected(), 3);
    QStandardItem *first=new QStandardItem("Название");
    QStandardItem *sec=new QStandardItem("Дата записи");
    QStandardItem *third=new QStandardItem("Вид");
    model->setHorizontalHeaderItem(0, first);
    model->setHorizontalHeaderItem(1, sec);
    model->setHorizontalHeaderItem(2, third);
    //QStandardItem *item;
    while (queryEng.next())
    {
        int UKEY=queryEng.value(recEng.indexOf("UKEY")).toInt();
        QString Name=queryEng.value(recEng.indexOf("Название")).toString();
        QModelIndex indexEng=model->index(UKEY-1, 0);
        model->setData(indexEng, Name);
        QDateTime Drec=queryEng.value(recEng.indexOf("Дата записи")).toDateTime();
        model->setData(model->index(UKEY-1, 1), Drec.toString("dd.MM.yyyy hh:mm:ss"));
        QString Sight=queryEng.value(recEng.indexOf("Вид")).toString();
        model->setData(model->index(UKEY-1, 2), Sight);
        QByteArray arr=queryEng.value(recEng.indexOf("Изображение")).toByteArray();
        //item=new QStandardItem;
        //item->setData(arr);
        model->setData(indexEng, arr, Qt::UserRole);

        queryAgr.bindValue(":KEY", UKEY);
        queryAgr.exec();
        recAgr=queryAgr.record();
        model->insertRows(0, queryAgr.numRowsAffected(), indexEng);
        model->insertColumns(0, 3, indexEng);
        int RowAgr=0;
        while (queryAgr.next())
        {
            Name=queryAgr.value(recAgr.indexOf("Название")).toString();
            QModelIndex indexAgr=model->index(RowAgr, 0, indexEng);
            model->setData(indexAgr, Name);
            Drec=queryAgr.value(recAgr.indexOf("Дата записи")).toDateTime();
            model->setData(model->index(RowAgr, 1, indexEng), Drec.toString("dd.MM.yyyy hh:mm:ss"));
            Sight=queryAgr.value(recAgr.indexOf("Вид")).toString();
            model->setData(model->index(RowAgr, 2, indexEng), Sight);

            UKEY=queryAgr.value(recAgr.indexOf("UKEY")).toInt();
            queryUn.bindValue(":KEY", UKEY);
            queryUn.exec();
            recUn=queryUn.record();
            model->insertRows(0, queryUn.numRowsAffected(), indexAgr);
            model->insertColumns(0, 3, indexAgr);
            int RowUn=0;
            while (queryUn.next())
            {
                Name=queryUn.value(recUn.indexOf("Название")).toString();
                QModelIndex indexUn=model->index(RowUn, 0, indexAgr);
                model->setData(indexUn, Name);
                Drec=queryUn.value(recUn.indexOf("Дата записи")).toDateTime();
                model->setData(model->index(RowUn, 1, indexAgr), Drec.toString("dd.MM.yyyy hh:mm:ss"));
                Sight=queryUn.value(recUn.indexOf("Вид")).toString();
                model->setData(model->index(RowUn, 2, indexAgr), Sight);
                RowUn++;
            }
            RowAgr++;
        }
    }
   return model;
    //ProBar *pgr=new ProBar;
//    QTreeWidgetItem *pitem=0;
//    QStringList lst;
//    lst<<"Название";
//    lv->setHeaderHidden(false);
//    lv->setHeaderLabels(lst);
//    QPixmap img;
//    QString str;
//    QByteArray arr;
//    QSqlQuery query(QSqlDatabase::database(QSqlDatabase::contains("first") ? "first" : "second"));
//    query.exec("Select * FROM [TestBaza].[dbo].[Photo]");
//    QSqlRecord rec=query.record();
    //pgr->Step(0);
    //int r=query.numRowsAffected();
    //int c=100/r+1, i=1;
//    while (query.next())
//    {
//        pitem = new QTreeWidgetItem(lv);
//        arr=query.value(rec.indexOf("Изображение")).toByteArray();
//        str=query.value(rec.indexOf("Название")).toString();
//        pitem->setText(0, str);
//        if (img.loadFromData(QByteArray::fromBase64(arr)))
//           pitem->setIcon(0, QPixmap(img));
        //pgr->Step(i*c);
        //i++;
        //qApp->processEvents();
//    }
    //pgr->Step(100);
    //pgr->close();
}
