#include "QBrowserApp.h"

QBrowserApp::QBrowserApp(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), m_mainWidget(new QWidget) {
    setCentralWidget(m_mainWidget);
    setWindowTitle(QObject::tr("QSqlBrowser"));

    QSplitter* splitter = new QSplitter(Qt::Vertical, m_mainWidget);
    QSqlCtrl* sqlctrl = new QSqlCtrl(splitter);
    QSqlQueryPanel* querypanel = new QSqlQueryPanel(splitter);

    splitter->setChildrenCollapsible(false);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->addWidget(sqlctrl);
    splitter->addWidget(querypanel);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);
    m_mainWidget->setLayout(mainLayout);
    m_mainWidget->setMinimumSize(820, 625);
}