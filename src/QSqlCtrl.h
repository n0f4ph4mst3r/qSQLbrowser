#pragma once

#ifndef SQLCTRL_H
#define SQLCTRL_H

#include <QSplitter>
#include <QFrame>
#include <QTreeWidget>
#include <QTableView>
#include <QApplication>
#include <QCursor>

#include "QConnectionDialog.h"

class QSqlCtrl : public QSplitter
{
	Q_OBJECT
protected:
	QTreeWidget* m_tree;
	QTableView* m_table;
public:
	explicit QSqlCtrl(QWidget* parent = nullptr);
};

#endif