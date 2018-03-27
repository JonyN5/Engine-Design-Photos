#ifndef DOWNLOADWIN_H
#define DOWNLOADWIN_H

#include <QMainWindow>
#include "QFileInfoList"
#include "QListWidgetItem"
//#include "dialogdownload.h"
#include "dw_info.h"
#include "dw_insert.h"
#include "setapp.h"

namespace Ui {
class DownloadWin;
}

class DownloadWin : public QMainWindow
{
    Q_OBJECT
public:
    explicit DownloadWin(QMainWindow *parent = 0);
    ~DownloadWin();
public slots:
    void InsertSlot(); //загрузка на сервер выбранных фотографий
    void Choice(); //идёт загрузка фотографий и инф по ним
private:
    Ui::DownloadWin *ui;
    //DialogDownload *dd;
    QList <QListWidgetItem*> Allitems;
    QSettings *pst=SetApp::theApp()->settings();
};

#endif // DOWNLOADWIN_H
