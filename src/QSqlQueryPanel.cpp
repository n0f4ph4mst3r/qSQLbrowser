#include "QSqlQueryPanel.h"

QSqlQueryPanel::QSqlQueryPanel(QWidget* parent, Qt::WindowFlags f) : QFrame(parent, f) {
    QPushButton* clearButton = new QPushButton(tr("Clear"));
    QWidget* buttonpanel = new QWidget;
    QHBoxLayout* buttonHLayout = new QHBoxLayout;
    buttonHLayout->addWidget(clearButton, 1, Qt::AlignRight);
    buttonHLayout->addWidget(new QPushButton(tr("Submit")), 0);
    buttonpanel->setLayout(buttonHLayout);

    QPlainTextEdit* textBox = new QPlainTextEdit;
    textBox->setPlaceholderText(tr("SQL Query"));
    connect(clearButton, &QPushButton::clicked, this, [=]() {textBox->clear(); textBox->setFocus();});

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(textBox, 1);
    mainLayout->addWidget(buttonpanel);
    setLayout(mainLayout);

    setMinimumSize(800, 350);
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);
}
