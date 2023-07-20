#include "QBrowserApp.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

#ifndef Q_OS_WINDOWS
    QApplication::setWindowIcon(QIcon(":/app_icon/app_icon.xpm"));
#endif

    QBrowserApp browser;
    browser.show();

    QConnectionDialog dialog(&browser);
    dialog.exec();

    return app.exec();
}