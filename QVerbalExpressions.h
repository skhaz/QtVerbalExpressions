
#ifndef _QVerbalExpressions_h
#define _QVerbalExpressions_h

#include <QChar>
#include <QString>
#include <QRegExp>

#ifdef Q_COMPILER_INITIALIZER_LISTS
#include <initializer_list>
#endif

class QVerbalExpressions
{
    public:
        QVerbalExpressions();

        QVerbalExpressions& add(const QString& value = QString());
        QVerbalExpressions& startOfLine(bool enable = true);
        QVerbalExpressions& endOfLine(bool enable = true);
        QVerbalExpressions& then(const QString& value);
        QVerbalExpressions& find(const QString& value);
        QVerbalExpressions& maybe(const QString& value);
        QVerbalExpressions& anything();
        QVerbalExpressions& anythingBut(const QString& value);
        QVerbalExpressions& something();
        QVerbalExpressions& somethingBut(const QString& value);
        QVerbalExpressions& lineBreak();
        QVerbalExpressions& br();
        QVerbalExpressions& tab();
        QVerbalExpressions& word();
        QVerbalExpressions& anyOf(const QString& value);
        QVerbalExpressions& any(const QString& value);
        QVerbalExpressions& addModifier(char modifier);
        QVerbalExpressions& removeModifier(char modifier);
        QVerbalExpressions& withAnyCase(bool enable = true);
        QVerbalExpressions& searchOneLine(bool enable = true);
        QVerbalExpressions& searchGlobal(bool enable = true);
        QVerbalExpressions& multiple(const QString& value);
        QVerbalExpressions& alt(const QString& value);

        #ifdef Q_COMPILER_INITIALIZER_LISTS
        QVerbalExpressions& range(const std::initializer_list<QString> & args);
        #endif

        bool test(const QString& value);

        const QString replace(const QString& source, const QString& value);

        unsigned int modifiers;

    protected:
        unsigned int checkFlags();

        const QString reduceLines(const QString& value);

    private:
        enum Flags {
            GLOBAL = 1,
            MULTILINE = 2,
            CASEINSENSITIVE = 4
        };

        QString prefixes;
        QString	source;
        QString suffixes;
        QString pattern;
};

#endif
