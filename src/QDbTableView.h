#pragma once

#ifndef DBTABLEVIEW_H
#define DBTABLEVIEW_H

#include <QObject>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlField>
#include <QStandardItemModel>

class QDbTableView : public QTableView
{
	Q_OBJECT;
public:
	explicit QDbTableView(QWidget* parent = nullptr);
public slots:
	void setTableModel(QAbstractItemModel* model, QAbstractItemView::EditTriggers triggers);
protected:
	QAction* m_selectAction;
	QAction* m_insertRowAction;
	QAction* m_deleteRowAction;
	QAction* m_fieldStrategyAction;
	QAction* m_rowStrategyAction;
	QAction* m_manualStrategyAction;
	QAction* m_submitAction;
	QAction* m_revertAction;

	void insertRow();
	void deleteRow();
	void updateActions();
};

#endif