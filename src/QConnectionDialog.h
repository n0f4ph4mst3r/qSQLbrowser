#pragma once

#ifndef QSQLCONNECTIONDIALOG_H
#define QSQLCONNECTIONDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QSqlDatabase>
#include <QApplication>

class QConnectionDialog : public QDialog
{
	Q_OBJECT
public:
	QConnectionDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};

#endif