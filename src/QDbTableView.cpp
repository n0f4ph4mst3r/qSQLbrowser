#include "QDbTableView.h"

QDbTableView::QDbTableView(QWidget* parent) {
    m_selectAction = new QAction(tr("Select"), this);
    m_insertRowAction = new QAction(tr("Insert Row"), this);
    m_deleteRowAction = new QAction(tr("Delete Row"), this);
    m_fieldStrategyAction = new QAction(tr("Submit on Field Change"), this);
    m_rowStrategyAction = new QAction(tr("Submit on Row Change"), this);
    m_manualStrategyAction = new QAction(tr("Submit Manually"), this);
    m_submitAction = new QAction(tr("Submit All"), this);
    m_revertAction = new QAction(tr("Revert All"), this);

    m_fieldStrategyAction->setCheckable(true);
    m_rowStrategyAction->setCheckable(true);
    m_manualStrategyAction->setCheckable(true);

    auto f_getModel = [=]() { return qobject_cast<QSqlTableModel*>(model()); };
    connect(m_selectAction, &QAction::triggered, this, [=]() { auto tm = f_getModel(); if (tm) tm->select(); });
    connect(m_insertRowAction, &QAction::triggered, this, &QDbTableView::insertRow);
    connect(m_deleteRowAction, &QAction::triggered, this, &QDbTableView::deleteRow);
    connect(m_fieldStrategyAction, &QAction::triggered, this, [=]() { auto tm = f_getModel(); if (tm) tm->setEditStrategy(QSqlTableModel::OnFieldChange); });
    connect(m_rowStrategyAction, &QAction::triggered, this, [=]() { auto tm = f_getModel(); if (tm) tm->setEditStrategy(QSqlTableModel::OnFieldChange); });
    connect(m_manualStrategyAction, &QAction::triggered, this, [=]() { auto tm = f_getModel(); if (tm) tm->setEditStrategy(QSqlTableModel::OnRowChange); });
    connect(m_submitAction, &QAction::triggered, this, [=]() { auto tm = f_getModel(); if (tm) tm->submitAll(); });
    connect(m_revertAction, &QAction::triggered, this, [=]() { auto tm = f_getModel(); if (tm) tm->revertAll(); });

    auto f_createSeparator = [=]() {QAction* separator = new QAction; separator->setSeparator(true); return separator; };
    addAction(m_selectAction);
    addAction(m_insertRowAction);
    addAction(m_deleteRowAction);
    addAction(f_createSeparator());
    addAction(m_fieldStrategyAction);
    addAction(m_rowStrategyAction);
    addAction(m_manualStrategyAction);
    addAction(f_createSeparator());
    addAction(m_submitAction);
    addAction(m_revertAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setMinimumSize(300, 252);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);
}

void QDbTableView::setTableModel(QAbstractItemModel* model, QAbstractItemView::EditTriggers triggers) {
    model->setParent(this);
    setModel(model);
    setEditTriggers(triggers);
    if (triggers != QAbstractItemView::NoEditTriggers)
        connect(selectionModel(), &QItemSelectionModel::currentRowChanged, this, [=] {updateActions(); });
    updateActions();
}

void QDbTableView::insertRow() {
    auto tm = qobject_cast<QSqlTableModel*>(model());
    if (!tm)
        return;

    QModelIndex insertIndex = currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    tm->insertRow(row);
    insertIndex = tm->index(row, 0);
    setCurrentIndex(insertIndex);
    edit(insertIndex);
}

void QDbTableView::deleteRow() {
    auto tm = qobject_cast<QSqlTableModel*>(model());
    if (!tm)
        return;

    QModelIndexList currentSelection = selectionModel()->selectedIndexes();
    for (int i = 0; i < currentSelection.count(); ++i) {
        if (currentSelection.at(i).column() != 0)
            continue;
        tm->removeRow(currentSelection.at(i).row());
    }

    updateActions();
}

void QDbTableView::updateActions() {
    auto tm = qobject_cast<QSqlTableModel*>(model());
    bool enableIns = tm;
    bool enableDel = enableIns && currentIndex().isValid();

    m_insertRowAction->setEnabled(enableIns);
    m_deleteRowAction->setEnabled(enableDel);

    m_fieldStrategyAction->setEnabled(tm);
    m_rowStrategyAction->setEnabled(tm);
    m_manualStrategyAction->setEnabled(tm);
    m_submitAction->setEnabled(tm);
    m_revertAction->setEnabled(tm);
    m_selectAction->setEnabled(tm);

    if (tm) {
        QSqlTableModel::EditStrategy es = tm->editStrategy();
        m_fieldStrategyAction->setChecked(es == QSqlTableModel::OnFieldChange);
        m_rowStrategyAction->setChecked(es == QSqlTableModel::OnRowChange);
        m_manualStrategyAction->setChecked(es == QSqlTableModel::OnManualSubmit);
    }
}
