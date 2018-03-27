#include "Authorization_menu.h"
#include "setapp.h"

int main(int argc, char *argv[])
{
    SetApp app(argc, argv, "KBHA", "EDP");
    Authorization_menu am;
    am.show();
    return app.exec();
}
