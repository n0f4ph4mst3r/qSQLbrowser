#include "QConnectionDialog.h"

QConnectionDialog::QConnectionDialog(QWidget* parent, Qt::WindowFlags f)
	: QDialog(parent, f) {
	setWindowTitle(QObject::tr("Connect..."));
	setMinimumSize(330, 300);

    QGroupBox* groupBox = new QGroupBox(QObject::tr("Connection settings"));
    QGridLayout* groupBoxLayout = new QGridLayout;

    QComboBox* comboBox = new QComboBox;
    QStringList drivers = QSqlDatabase::drivers();
    if (!drivers.contains("QSQLITE")) comboBox->setEnabled(false);
    comboBox->addItems(drivers);

    QSpinBox* spinBox = new QSpinBox;
    spinBox->setMaximum(65535);
    spinBox->setMinimum(-1);
    spinBox->setValue(-1);
    spinBox->setSpecialValueText(tr("Default"));

    groupBoxLayout->setSpacing(10);
    groupBoxLayout->addWidget(new QLabel(tr("Driver:")), 0, 0);
    groupBoxLayout->addWidget(comboBox, 0, 1);
    groupBoxLayout->addWidget(new QLabel(tr("Database Name:")), 1, 0);
    groupBoxLayout->addWidget(new QLineEdit, 1, 1);
    groupBoxLayout->addWidget(new QLabel(tr("Username:")), 2, 0);
    groupBoxLayout->addWidget(new QLineEdit, 2, 1);
    groupBoxLayout->addWidget(new QLabel(tr("Password:")), 3, 0);
    groupBoxLayout->addWidget(new QLineEdit, 3, 1);
    groupBoxLayout->addWidget(new QLabel(tr("Hostname:")), 4, 0);
    groupBoxLayout->addWidget(new QLineEdit, 4, 1);
    groupBoxLayout->addWidget(new QLabel(tr("Port: ")), 5, 0);
    groupBoxLayout->addWidget(spinBox, 5, 1);
    groupBox->setLayout(groupBoxLayout);

    QPushButton* acceptButton = new QPushButton(tr("OK"));
    QPushButton* rejectButton = new QPushButton(tr("Cancel"));
    connect(acceptButton, &QPushButton::clicked, this, [=]() {accept(); });
    connect(rejectButton, &QPushButton::clicked, this, [=]() {reject();; });

    QWidget* buttonpanel = new QWidget;
    QHBoxLayout* buttonHLayout = new QHBoxLayout;
    buttonHLayout->addWidget(acceptButton, 1, Qt::AlignRight);
    buttonHLayout->addWidget(rejectButton, 0);
    buttonpanel->setLayout(buttonHLayout);

    QVBoxLayout* dialogLayout = new QVBoxLayout;
    dialogLayout->addWidget(groupBox);
    dialogLayout->addWidget(buttonpanel);
    setLayout(dialogLayout);

#ifdef Q_OS_WINDOWS
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_CommandLink));
#endif
}