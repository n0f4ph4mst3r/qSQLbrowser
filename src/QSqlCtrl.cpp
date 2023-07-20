#include "QSqlCtrl.h"

QSqlCtrl::QSqlCtrl(QWidget* parent) : QSplitter(parent) {
	setChildrenCollapsible(false);

    m_tree = new QTreeWidget(this);
    m_tree->setMinimumSize(200, 252);
    QTreeWidgetItem* rootItem = new QTreeWidgetItem();
    rootItem->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon));
    rootItem->setText(0, tr("database"));
    m_tree->setHeaderItem(rootItem);
    m_tree->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_tree->setLineWidth(2);

    m_table = new QTableView(this);
    m_table->setMinimumSize(200, 252);
    m_table->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_table->setLineWidth(2);

    addWidget(m_tree);
    addWidget(m_table);
    setStretchFactor(0, 0);
    setStretchFactor(1, 1);
    setSizes({ 200, 600 });

    auto sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);
    m_tree->setSizePolicy(sizePolicy);
    m_table->setSizePolicy(sizePolicy);

    QAction* addConnectionAction = new QAction(tr("Add Connection..."), m_tree);
    connect(addConnectionAction, &QAction::triggered, this, [=]() { QConnectionDialog dialog(this); dialog.exec(); });
    m_tree->addAction(addConnectionAction);

    m_tree->setContextMenuPolicy(Qt::ActionsContextMenu);
}