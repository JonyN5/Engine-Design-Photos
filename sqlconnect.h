#ifndef SQLCONNECT_H
#define SQLCONNECT_H
#include "QtSql"
#include "QString"
#include "QStringList"
#include "QDateTime"
#include "QStandardItemModel"
#include "QByteArray"
#include "QMessageBox"
//template <typename L>

class SQLconnect
{
public:
   SQLconnect(QString DB, QString User, QString Host, QString Pass, QString Driver);
   bool createConnection ();
   static int countRecords(int tabl);
   static void InsertQuery(int FK,
                           QString Name,
                           QString *Bt64str,
                           QString *suf,
                           QString BirthD,
                           QString ModifiedD,
                           QString SightCh,
                           int tabl);
   static QStandardItemModel *SelectQuery();
   static QList <int> SelectKey(int tabl, int FK=0);
   static QStringList SelectName(int tabl, int FK=0);
private:
   QString DBName,
           UserName,
           HostName,
           Password,
           DrivName;
   QSqlDatabase db;  
};

#endif // SQLCONNECT_H
