#include "Authorization_menu.h"
#include "setapp.h"

int main(int argc, char *argv[])
{
    SetApp app(argc, argv, "KBHA", "EDP");
    //EDPMain mw;
    Authorization_menu am;
    //mw.show();
    am.show();
    return app.exec();
}
