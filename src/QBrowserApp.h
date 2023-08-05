#pragma once

#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>
#include <QStatusBar>
#include <QSplitter>
#include <QFrame>
#include <QMenuBar>

#include "QConnectionCtrl.h"
#include "QDbTableView.h"
#include "QSqlQueryPanel.h"

class QBrowserApp : public QMainWindow
{
	Q_OBJECT
protected:
	QWidget* m_mainWidget;

	QConnectionCtrl* m_tree;
	QDbTableView* m_table;
public:
	explicit QBrowserApp(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
public slots:
	void about();
};

#endif