#pragma once

#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>

#include "QSqlCtrl.h"
#include "QSqlQueryPanel.h"

class QBrowserApp : public QMainWindow
{
	Q_OBJECT
protected:
	QWidget* m_mainWidget;
public:
	explicit QBrowserApp(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
};

#endif