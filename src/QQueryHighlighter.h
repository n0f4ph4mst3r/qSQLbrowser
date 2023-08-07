// SPDX-FileCopyrightText: 2023 Korshunov Vladislav <vladredsoup@gmail.com>
// SPDX-License-Identifier: (GPL-3.0-only)

#pragma once

#ifndef QUERYHIGHTLIGHTER_H
#define QUERYHIGHTLIGHTER_H

#include <algorithm>
#include <QSyntaxHighlighter>
#include <QRegularExpression>

class QQueryHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    QQueryHighlighter(QTextDocument* parent = nullptr);

protected:
    void highlightBlock(const QString& text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QList<HighlightingRule> m_highlightingRules;

    QRegularExpression m_sLiteralDelimiterExpression;

    QRegularExpression m_commentStartExpression;
    QRegularExpression m_commentEndExpression;

    QTextCharFormat m_keywordFormat;
    QTextCharFormat m_sLiteralFormat;
    QTextCharFormat m_dLiteralFormat;
    QTextCharFormat m_singleLineCommentFormat;
    QTextCharFormat m_multiLineCommentFormat;
};

#endif
