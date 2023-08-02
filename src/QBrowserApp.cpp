#include "QBrowserApp.h"

QBrowserApp::QBrowserApp(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), m_mainWidget(new QWidget) {
    setCentralWidget(m_mainWidget);
    setWindowTitle(QObject::tr("QSqlBrowser"));

    QSplitter* vSplitter = new QSplitter(Qt::Vertical, m_mainWidget);
    QSplitter* hSplitter = new QSplitter(vSplitter);

    hSplitter->setChildrenCollapsible(false);
    m_tree = new QConnectionCtrl(hSplitter);
    m_table = new QDbTableView(hSplitter);

    hSplitter->addWidget(m_tree);
    hSplitter->addWidget(m_table);
    hSplitter->setStretchFactor(0, 0);
    hSplitter->setStretchFactor(1, 1);
    hSplitter->setSizes({ 250, 550 });
    hSplitter->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    QSqlQueryPanel* querypanel = new QSqlQueryPanel(vSplitter);

    vSplitter->setChildrenCollapsible(false);
    vSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vSplitter->addWidget(hSplitter);
    vSplitter->addWidget(querypanel);
    vSplitter->setStretchFactor(0, 1);
    vSplitter->setStretchFactor(1, 0);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(vSplitter);
    m_mainWidget->setLayout(mainLayout);
    m_mainWidget->setMinimumSize(820, 625);

    QObject::connect(m_tree, &QConnectionCtrl::tableModelChanged, m_table, &QDbTableView::setTableModel);
    QObject::connect(m_tree, &QConnectionCtrl::statusMessage, [&](const QString& text) { statusBar()->showMessage(text); });
}