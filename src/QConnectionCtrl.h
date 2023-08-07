// SPDX-FileCopyrightText: 2023 Korshunov Vladislav <vladredsoup@gmail.com>
// SPDX-License-Identifier: (GPL-3.0-only)

#pragma once

#ifndef CONNECTIONCTRL_H
#define CONNECTIONCTRL_H

#include <QObject>
#include <QTreeWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>
#include <QStandardItemModel>
#include <QCursor>
#include <QBrush>

#include "QConnectionDialog.h"

class QConnectionCtrl : public QTreeWidget
{
	Q_OBJECT;
public:
	explicit QConnectionCtrl(QWidget* parent = nullptr);
	static QSqlError createConnection(const QString& driver, const QString& dbName, const QString& host, const QString& user, const QString& passwd, const int port = -1);
public slots:
	void addConnection(const QString& driver, const QString& dbName, const QString& host, const QString& user, const QString& passwd, const int port = -1);
	void showConnectionDialog();
	void showMetaData();
	void setActiveItem(QTreeWidgetItem* item, int column);
signals:
	void tableModelChanged(QAbstractItemModel* model, QAbstractItemView::EditTriggers triggers);
	void statusMessage(const QString& message);
	void dbSelected(const QString& db);
protected:
	QString m_activeDb;

	void refresh();
	void setActiveDb(QTreeWidgetItem* item);
};

class CustomModel : public QSqlTableModel
{
	Q_OBJECT
public:
	explicit CustomModel(QObject* parent = nullptr, QSqlDatabase db = QSqlDatabase())
		: QSqlTableModel(parent, db) {}

	QVariant data(const QModelIndex& idx, int role) const override
	{
		if (role == Qt::BackgroundRole && isDirty(idx))
			return QBrush(QColor(255, 0, 0, 127));
		return QSqlTableModel::data(idx, role);
	}
};

#endif