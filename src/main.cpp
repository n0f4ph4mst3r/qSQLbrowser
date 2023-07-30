#include "QBrowserApp.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    const QStringList& args = app.arguments();
    for (int i = 1; i < args.count(); ++i) {
        QUrl url(args.at(i), QUrl::TolerantMode);
        if (!url.isValid()) {
            qWarning("Invalid URL: %s", qPrintable(args.at(i)));
            continue;
        }
        QSqlError err = QConnectionCtrl::createConnection(url.scheme(), url.path().mid(1), url.host(), url.userName(), url.password(), url.port(-1));
        if (err.type() != QSqlError::NoError)
            qDebug() << "Unable to open connection:" << err;
    }

#ifndef Q_OS_WINDOWS
    QApplication::setWindowIcon(QIcon(":/app_icon/app_icon.xpm"));
#endif

    QBrowserApp browser;
    browser.show();
    if (QSqlDatabase::connectionNames().isEmpty())
        QMetaObject::invokeMethod(browser.findChild<QConnectionCtrl*>("connectionCtrl"), "showConnectionDialog", Qt::QueuedConnection);

    return app.exec();
}