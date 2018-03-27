#ifndef SQLCONNECT_H
#define SQLCONNECT_H
#include "QString"
#include "QtSql"
#include "QTreeWidget"
#include "QStringList"

class SQLconnect
{
public:
   SQLconnect(QString DB, QString User, QString Host, QString Pass, QString Driver);
   bool createConnection ();
   static void InsertQuery(QString *Name, QString *bt64, QString *suf);
   static void SelectQuery(QTreeWidget *lv);
private:
   QString DBName,
           UserName,
           HostName,
           Password,
           DrivName;
   QSqlDatabase db;
   QStringList drvs; //список доступных драйверов
};

#endif // SQLCONNECT_H
