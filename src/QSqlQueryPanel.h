#pragma once

#ifndef QUERYPANEL_H
#define QUERYPANEL_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

class QSqlQueryPanel : public QFrame
{
	Q_OBJECT
public:
	explicit QSqlQueryPanel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};

#endif