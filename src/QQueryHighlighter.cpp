#include "QQueryHighlighter.h"

QQueryHighlighter::QQueryHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    m_keywordFormat.setForeground(Qt::darkMagenta);
    m_keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\b(?i)ADD(?-i)\\b"), 
        QStringLiteral("\\b(?i)ADD CONSTRAINT(?-i)\\b"),
        QStringLiteral("\\b(?i)ALL(?-i)\\b"),
        QStringLiteral("\\b(?i)ALTER(?-i)\\b"), 
        QStringLiteral("\\b(?i)ALTER COLUMN(?-i)\\b"),
        QStringLiteral("\\b(?i)ALTER TABLE(?-i)\\b"),
        QStringLiteral("\\b(?i)AND(?-i)\\b"),
        QStringLiteral("\\b(?i)ANY(?-i)\\b"), 
        QStringLiteral("\\b(?i)AS(?-i)\\b"),
        QStringLiteral("\\b(?i)ASC(?-i)\\b"),
        QStringLiteral("\\b(?i)AVG(?-i)\\b"),
        QStringLiteral("\\b(?i)BACKUP DATABASE(?-i)\\b"), 
        QStringLiteral("\\b(?i)BETWEEN(?-i)\\b"),
        QStringLiteral("\\b(?i)CASE(?-i)\\b"), 
        QStringLiteral("\\b(?i)CHECK(?-i)\\b"), 
        QStringLiteral("\\b(?i)COLUMN(?-i)\\b"),
        QStringLiteral("\\b(?i)CONSTRAINT(?-i)\\b"), 
        QStringLiteral("\\b(?i)COUNT(?-i)\\b"),
        QStringLiteral("\\b(?i)CREATE(?-i)\\b"), 
        QStringLiteral("\\b(?i)CREATE DATABASE(?-i)\\b"),
        QStringLiteral("\\b(?i)CREATE INDEX(?-i)\\b"), 
        QStringLiteral("\\b(?i)CREATE OR REPLACE VIEW(?-i)\\b"),
        QStringLiteral("\\b(?i)CREATE TABLE(?-i)\\b"),
        QStringLiteral("\\b(?i)CREATE PROCEDURE(?-i)\\b"),
        QStringLiteral("\\b(?i)CREATE UNIQUE INDEX(?-i)\\b"), 
        QStringLiteral("\\b(?i)CREATE VIEW(?-i)\\b"),
        QStringLiteral("\\b(?i)DATABASE(?-i)\\b"), 
        QStringLiteral("\\b(?i)DEFAULT(?-i)\\b"), 
        QStringLiteral("\\b(?i)DELETE(?-i)\\b"),
        QStringLiteral("\\b(?i)DESC(?-i)\\b"), 
        QStringLiteral("\\b(?i)DISTINCT(?-i)\\b"), 
        QStringLiteral("\\b(?i)DROP(?-i)\\b"),
        QStringLiteral("\\b(?i)DROP COLUMN(?-i)\\b"),
        QStringLiteral("\\b(?i)DROP CONSTRAINT(?-i)\\b"),
        QStringLiteral("\\b(?i)DROP DATABASE(?-i)\\b"),
        QStringLiteral("\\b(?i)DROP DEFAULT(?-i)\\b"),
        QStringLiteral("\\b(?i)DROP INDEX(?-i)\\b"),
        QStringLiteral("\\b(?i)DROP TABLE(?-i)\\b"),
        QStringLiteral("\\b(?i)DROP VIEW(?-i)\\b"),
        QStringLiteral("\\b(?i)EXEC(?-i)\\b"),
        QStringLiteral("\\b(?i)EXISTS(?-i)\\b"),
        QStringLiteral("\\b(?i)FOREIGN KEY(?-i)\\b"),
        QStringLiteral("\\b(?i)FROM(?-i)\\b"),
        QStringLiteral("\\b(?i)FULL OUTER JOIN(?-i)\\b"),
        QStringLiteral("\\b(?i)GROUP BY(?-i)\\b"),
        QStringLiteral("\\b(?i)HAVING(?-i)\\b"),
        QStringLiteral("\\b(?i)IN(?-i)\\b"),
        QStringLiteral("\\b(?i)INDEX(?-i)\\b"),
        QStringLiteral("\\b(?i)INNER JOIN(?-i)\\b"),
        QStringLiteral("\\b(?i)INSERT INTO(?-i)\\b"),
        QStringLiteral("\\b(?i)INSERT INTO SELECT(?-i)\\b"),
        QStringLiteral("\\b(?i)IS NULL(?-i)\\b"),
        QStringLiteral("\\b(?i)IS NOT NULL(?-i)\\b"),
        QStringLiteral("\\b(?i)JOIN(?-i)\\b"),
        QStringLiteral("\\b(?i)LEFT JOIN(?-i)\\b"),
        QStringLiteral("\\b(?i)LIKE(?-i)\\b"),
        QStringLiteral("\\b(?i)MAX(?-i)\\b"),
        QStringLiteral("\\b(?i)MIN(?-i)\\b"),
        QStringLiteral("\\b(?i)NOT(?-i)\\b"),
        QStringLiteral("\\b(?i)NOT NULL(?-i)\\b"),
        QStringLiteral("\\b(?i)OR(?-i)\\b"),
        QStringLiteral("\\b(?i)ORDER BY(?-i)\\b"),
        QStringLiteral("\\b(?i)OUTER JOIN(?-i)\\b"),
        QStringLiteral("\\b(?i)PRIMARY KEY(?-i)\\b"),
        QStringLiteral("\\b(?i)PROCEDURE(?-i)\\b"),
        QStringLiteral("\\b(?i)RIGHT JOIN(?-i)\\b"),
        QStringLiteral("\\b(?i)ROWNUM(?-i)\\b"),
        QStringLiteral("\\b(?i)SELECT(?-i)\\b"),
        QStringLiteral("\\b(?i)SELECT DISTINCT(?-i)\\b"),
        QStringLiteral("\\b(?i)SELECT INTO(?-i)\\b"),
        QStringLiteral("\\b(?i)SELECT TOP(?-i)\\b"),
        QStringLiteral("\\b(?i)SET(?-i)\\b"),
        QStringLiteral("\\b(?i)SUM(?-i)\\b"),
        QStringLiteral("\\b(?i)TABLE(?-i)\\b"),
        QStringLiteral("\\b(?i)TOP(?-i)\\b"),
        QStringLiteral("\\b(?i)TRUNCATE TABLE(?-i)\\b"),
        QStringLiteral("\\b(?i)UNION(?-i)\\b"),
        QStringLiteral("\\b(?i)UNION ALL(?-i)\\b"),
        QStringLiteral("\\b(?i)UNIQUE(?-i)\\b"),
        QStringLiteral("\\b(?i)UPDATE(?-i)\\b"),
        QStringLiteral("\\b(?i)VALUES(?-i)\\b"),
        QStringLiteral("\\b(?i)VIEW(?-i)\\b"),
        QStringLiteral("\\b(?i)WHERE(?-i)\\b")
    };

    for (auto pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_keywordFormat;
        m_highlightingRules.append(rule);
    }


    m_singleLineCommentFormat.setForeground(QColor(255, 0, 0, 127));
    rule.pattern = QRegularExpression(QStringLiteral("--[^\n]*"));
    rule.format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);

    m_sLiteralFormat.setForeground(Qt::gray);
    m_sLiteralFormat.setFontWeight(QFont::Bold);
    m_sLiteralDelimiterExpression = QRegularExpression(QStringLiteral("'"));

    m_dLiteralFormat.setForeground(Qt::darkRed);
    m_dLiteralFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)"));
    rule.format = m_dLiteralFormat;
    m_highlightingRules.append(rule);

    m_multiLineCommentFormat.setForeground(QColor(255, 0, 0, 127));
    m_commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    m_commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void QQueryHighlighter::highlightBlock(const QString& text) {
    for (const HighlightingRule& rule : std::as_const(m_highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);
    qsizetype startIndex = -1;
    qsizetype commentIndex = previousBlockState() != 1 ? text.indexOf(m_commentStartExpression) : 0;
    qsizetype literalIndex = previousBlockState() != 2 ? text.indexOf(m_sLiteralDelimiterExpression) : 0;
    if (commentIndex >= 0 && literalIndex >= 0)
        startIndex = std::min(commentIndex, literalIndex);
    else if (commentIndex >= 0)
        startIndex = commentIndex;
    else if (literalIndex >= 0)
        startIndex = literalIndex;

    while (startIndex >= 0) {
        qsizetype blockLength = 0;
        int blockState;
        QTextCharFormat fmt;
        if (startIndex == commentIndex) {
            blockState = 1;
            fmt = m_multiLineCommentFormat;
        }
        else {
            blockState = 2;
            fmt = m_sLiteralFormat;
        }

        QRegularExpressionMatch match = startIndex == literalIndex ? m_sLiteralDelimiterExpression.match(text, startIndex + 1) : m_commentEndExpression.match(text, startIndex + 2) ;
        qsizetype endIndex = match.capturedStart();
        if (endIndex == -1) {
            setCurrentBlockState(blockState);
            blockLength = text.length() - startIndex;
        }
        else blockLength = endIndex - startIndex + match.capturedLength();

        setFormat(startIndex, blockLength, fmt);

        commentIndex = text.indexOf(m_commentStartExpression, startIndex + blockLength);
        literalIndex = text.indexOf(m_sLiteralDelimiterExpression, startIndex + blockLength);
        startIndex = -1;
        if (commentIndex >= 0 && literalIndex >= 0)
            startIndex = std::min(commentIndex, literalIndex);
        else if (commentIndex >= 0)
            startIndex = commentIndex;
        else if (literalIndex >= 0)
            startIndex = literalIndex;
    }
}
