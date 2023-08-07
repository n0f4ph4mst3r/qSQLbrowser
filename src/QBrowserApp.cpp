// SPDX-FileCopyrightText: 2023 Korshunov Vladislav <vladredsoup@gmail.com>
// SPDX-License-Identifier: (GPL-3.0-only)

#include "QBrowserApp.h"

QBrowserApp::QBrowserApp(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), m_mainWidget(new QWidget) {
    setCentralWidget(m_mainWidget);
    setWindowTitle(QObject::tr("qSQLBrowser"));

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

    QMenu* mainMenu = menuBar()->addMenu(QObject::tr("&General"));
    mainMenu->addAction(QIcon(":/icons/dbConnect.png"), QObject::tr("Add &Connection..."), [&]() { QMetaObject::invokeMethod(findChild<QConnectionCtrl*>("connectionCtrl"), "showConnectionDialog", Qt::QueuedConnection); });
    mainMenu->addSeparator();
    mainMenu->addAction(QIcon(":/icons/quit.png"), QObject::tr("&Quit"), []() { qApp->quit(); });

    QMenu* helpMenu = menuBar()->addMenu(QObject::tr("&Help"));
    helpMenu->addAction(QIcon(":/icons/app_icon.png"), QObject::tr("About"), [&]() { about(); });
    helpMenu->addAction(QApplication::style()->standardIcon(QStyle::SP_TitleBarMenuButton), QObject::tr("About Qt"), []() { qApp->aboutQt(); });

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(vSplitter);
    m_mainWidget->setLayout(mainLayout);
    m_mainWidget->setMinimumSize(820, 625);

    QObject::connect(m_tree, &QConnectionCtrl::tableModelChanged, m_table, &QDbTableView::setTableModel);
    QObject::connect(querypanel, &QSqlQueryPanel::tableModelChanged, m_table, &QDbTableView::setTableModel);
    QObject::connect(m_tree, &QConnectionCtrl::dbSelected, querypanel, &QSqlQueryPanel::dbChange);
    QObject::connect(m_tree, &QConnectionCtrl::statusMessage, [&](const QString& text) { statusBar()->showMessage(text); });
    QObject::connect(querypanel, &QSqlQueryPanel::statusMessage, [&](const QString& text) { statusBar()->showMessage(text); });
}

void QBrowserApp::about() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setTextFormat(Qt::MarkdownText);
    msgBox.setText(tr("### qSQLbrowser\r\n"
        "Browser for visualizing the results of SQL statements on a live database.\r\n"
        "#### Author\r\n"
        "Korshunov Vladislav \\<vladredsoup@gmail.com\\>\n\n"
        "[License](https://github.com/n0f4ph4mst3r/qSQLbrowser/blob/master/LICENSE.txt) | [GitHub](https://github.com/n0f4ph4mst3r/qSQLbrowser)"));
    msgBox.setIconPixmap(QPixmap(":/icons/app_icon.png"));
    msgBox.exec();
}