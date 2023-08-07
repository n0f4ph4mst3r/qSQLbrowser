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
#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>

class QConnectionDialog : public QDialog
{
	Q_OBJECT
public:
	QConnectionDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
signals:
	void connectionAdded(const QString& driver, const QString& dbName, const QString& host, const QString& user, const QString& passwd, const int port = -1);
protected:
	QComboBox* comboBox;
	QLineEdit* dbEdit;
	QLineEdit* userEdit;
	QLineEdit* passwordEdit;
	QLineEdit* hostEdit;
	QSpinBox* spinBox;

	void on_accept();
};

#endif