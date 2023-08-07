#pragma once

#ifndef QUERYPANEL_H
#define QUERYPANEL_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QAbstractItemView>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

#include "QQueryHighlighter.h"

class QSqlQueryPanel : public QFrame
{
	Q_OBJECT
public:
	explicit QSqlQueryPanel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
public slots:
	void dbChange(const QString& db);
signals:
	void tableModelChanged(QAbstractItemModel* model, QAbstractItemView::EditTriggers triggers);
	void statusMessage(const QString& message);
protected:
	QString m_activeDb;
	void exec();
};

#endif