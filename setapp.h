#ifndef SETAPP_H
#define SETAPP_H
#include <QApplication>
#include <QSettings>

class SetApp : public QApplication
{
public:
    SetApp(int &argc,
           char** argv,
           const QString &strOrg,
           const QString &strAppname);
    static SetApp* theApp();
    QSettings* settings();
private:
    QSettings *m_pSettings;
};

#endif // SETAPP_H
