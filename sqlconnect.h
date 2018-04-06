#ifndef SQLCONNECT_H
#define SQLCONNECT_H
#include "QtSql"
#include "QString"
#include "QStringList"
#include "QDateTime"
#include "QStandardItemModel"
#include "QByteArray"
#include "QMessageBox"
#include "QObject"

class SQLconnect : public QObject
{
   Q_OBJECT
public:
   SQLconnect(QString DB, QString User, QString Host, QString Pass, QString Driver);
   SQLconnect();
   bool createConnection ();
   //static int countRecords(int tabl);
   static bool InsertQuery(int FK,
                           QString Name,
                           QString *Bt64str,
                           QString *suf,
                           QString BirthD,
                           QString ModifiedD,
                           QString SightCh,
                           int tabl,
                           int UKEY);
   QStandardItemModel *SelectQuery();
   //static QList <int> SelectKey(int tabl, int FK=0);
   static QStringList SelectName(int tabl, int FK=0);
signals:
   void ShowProgBar(bool);
   void StepProgBar(int);
private:
   QString DBName,
           UserName,
           HostName,
           Password,
           DrivName;
   QSqlDatabase db;  
};

#endif // SQLCONNECT_H
