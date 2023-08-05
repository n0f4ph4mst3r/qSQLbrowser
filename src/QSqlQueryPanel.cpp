// SPDX-FileCopyrightText: 2023 Korshunov Vladislav <vladredsoup@gmail.com>
// SPDX-License-Identifier: (GPL-3.0-only)

#include "QSqlQueryPanel.h"

QSqlQueryPanel::QSqlQueryPanel(QWidget* parent, Qt::WindowFlags f) : QFrame(parent, f) {
    QPushButton* submitButton = new QPushButton(tr("Submit"));

    QPushButton* clearButton = new QPushButton(tr("Clear"));
    QWidget* buttonpanel = new QWidget;
    QHBoxLayout* buttonHLayout = new QHBoxLayout;
    buttonHLayout->addWidget(clearButton, 1, Qt::AlignRight);
    buttonHLayout->addWidget(submitButton, 0);
    buttonpanel->setLayout(buttonHLayout);

    QPlainTextEdit* textBox = new QPlainTextEdit;
    textBox->setPlaceholderText(tr("SQL Query"));
    textBox->setObjectName("textBox");
    textBox->setFrameStyle(QFrame::NoFrame);
    QQueryHighlighter* highlighter = new QQueryHighlighter(textBox->document());

    connect(submitButton, &QPushButton::clicked, this, &QSqlQueryPanel::exec);
    connect(clearButton, &QPushButton::clicked, this, [=]() {textBox->clear(); textBox->setFocus(); });

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(textBox, 1);
    mainLayout->addWidget(buttonpanel);
    setLayout(mainLayout);

    setMinimumSize(800, 200);
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);
}

void QSqlQueryPanel::dbChange(const QString& db) {
    m_activeDb = db;
}

void QSqlQueryPanel::exec() {

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(QSqlQuery(findChild<QPlainTextEdit*>("textBox")->toPlainText(), QSqlDatabase::database(m_activeDb)));

    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());
    else if (model->query().isSelect())
        emit statusMessage(tr("Query OK."));
    else
        emit statusMessage(tr("Query OK, number of affected rows: %1").arg(model->query().numRowsAffected()));

    emit tableModelChanged(model, QAbstractItemView::NoEditTriggers);
    findChild<QPlainTextEdit*>("textBox")->setFocus();
}