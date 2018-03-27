#include "setapp.h"

SetApp::SetApp(int &argc,
               char **argv,
               const QString &strOrg,
               const QString &strAppname):
                QApplication(argc, argv),
                m_pSettings(0)
{
    setOrganizationName(strOrg);
    setApplicationName(strAppname);
    m_pSettings=new QSettings(strOrg, strAppname, this);
}

SetApp *SetApp::theApp()
{
    return (SetApp*)qApp;
}

QSettings *SetApp::settings()
{
    return m_pSettings;
}
