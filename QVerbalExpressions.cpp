
#include <QDebug>
#include "QVerbalExpressions.h"

QVerbalExpressions::QVerbalExpressions()
: modifiers(0)
{
}

QVerbalExpressions& QVerbalExpressions::add(const QString& value)
{
    source += value;
    pattern = prefixes % source % suffixes;

    return *this;
}

QVerbalExpressions& QVerbalExpressions::startOfLine(bool enable)
{
    prefixes = enable ? "^" : "";
    return add();
}

QVerbalExpressions& QVerbalExpressions::endOfLine(bool enable)
{
    suffixes = enable ? "$" : "";
    return add();
}

QVerbalExpressions& QVerbalExpressions::then(const QString& value)
{
    return add("(?:" % value % ")");
}

QVerbalExpressions& QVerbalExpressions::find(const QString& value)
{
    return then(value);
}

QVerbalExpressions& QVerbalExpressions::maybe(const QString& value)
{
    return add("(?:" % value % ")?");
}

QVerbalExpressions& QVerbalExpressions::anything()
{
    return add("(?:.*)");
}

QVerbalExpressions& QVerbalExpressions::anythingBut(const QString& value)
{
    return add("(?:[^" % value % "]*)");
}

QVerbalExpressions& QVerbalExpressions::something()
{
    return add("(?:.+)");
}

QVerbalExpressions& QVerbalExpressions::somethingBut(const QString& value)
{
    return add("(?:[^" % value % "]+)");
}

QVerbalExpressions& QVerbalExpressions::lineBreak()
{
    return add("(?:(?:\\n)|(?:\\r\\n))");
}

QVerbalExpressions& QVerbalExpressions::br()
{
    return lineBreak();
}

QVerbalExpressions& QVerbalExpressions::tab()
{
    return add("\\t");
}

QVerbalExpressions& QVerbalExpressions::word()
{
    return add("\\w+");
}

QVerbalExpressions& QVerbalExpressions::anyOf(const QString& value)
{
    return add("[" % value % "]");
}

QVerbalExpressions& QVerbalExpressions::any(const QString& value)
{
    return anyOf(value);
}

QVerbalExpressions& QVerbalExpressions::addModifier(char modifier)
{
    switch (modifier)
    {
        case 'i':
            modifiers |= QRegularExpression::CaseInsensitiveOption;
            break;

        case 'm':
            modifiers |= QRegularExpression::MultilineOption;
            break;

        case 'g':
            // TODO
            break;

        default:
            break;
    }

    return *this;
}

QVerbalExpressions& QVerbalExpressions::removeModifier(char modifier)
{
    switch (modifier)
    {
        case 'i':
            modifiers ^= QRegularExpression::CaseInsensitiveOption;
            break;

        case 'm':
            modifiers ^= QRegularExpression::MultilineOption;
            break;

        case 'g':
            // TODO
            break;

        default:
            break;
    }

    return *this;

}

QVerbalExpressions& QVerbalExpressions::withAnyCase(bool enable)
{
    if (enable)
        addModifier('i');
    else
        removeModifier('i');

    return *this;
}

QVerbalExpressions& QVerbalExpressions::searchOneLine(bool enable)
{
    if (enable)
        removeModifier('m');
    else
        addModifier('m');

    return *this;
}

QVerbalExpressions& QVerbalExpressions::searchGlobal(bool enable)
{
    if (enable)
        addModifier('g');
    else
        removeModifier('g');

    return *this;
}

QVerbalExpressions& QVerbalExpressions::multiple(const QString& value)
{
    if (!value.startsWith('*') || !value.startsWith('*'))
        add("+");

    return add(value);
}

QVerbalExpressions& QVerbalExpressions::alt(const QString& value)
{
    if (!prefixes.contains('('))
        prefixes += '(';

    if (!suffixes.contains(')'))
        suffixes = ')' % suffixes;

    add(")|(");
    return then(value);
}

#ifdef Q_COMPILER_INITIALIZER_LISTS
QVerbalExpressions& QVerbalExpressions::range(const std::initializer_list<QString> & args)
{
    // TODO
    return *this;
}
#endif

bool QVerbalExpressions::test(const QString& value)
{
    /// TODO

    return value.contains(QRegularExpression(pattern, modifiers));
}

QString QVerbalExpressions::replace(QString& source, const QString& value)
{
    return source.replace(QRegularExpression(pattern), value);
}
