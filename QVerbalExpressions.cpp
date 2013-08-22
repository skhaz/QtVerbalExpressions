
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
    prefixes = enabled ? "^" : "";
    return add();
}

QVerbalExpressions& QVerbalExpressions::endOfLine(bool enable)
{
    prefixes = enabled ? "$" : "";
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
            modifiers |= CASEINSENSITIVE;
            break;

        case 'm':
            modifiers |= MULTILINE;
            break;

        case 'g':
            modifiers |= GLOBAL;
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
            modifiers ^= CASEINSENSITIVE;
            break;

        case 'm':
            modifiers ^= MULTILINE;
            break;

        case 'g':
            modifiers ^= GLOBAL;
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
    if (!value.startsWith(QChar('*')) || !value.startsWith(QChar('*')))
        add("+");

    return add(value);
}

QVerbalExpressions& QVerbalExpressions::alt(const QString& value)
{
    if (!prefixes.contains(QChar('(')))
        prefixes += QChar('(');

    if (!suffixes.contains(QChar(')')))
        suffixes = QChar(')') % suffixes;

    add(")|(");
    return then(value);
}

#ifdef Q_COMPILER_INITIALIZER_LISTS
QVerbalExpressions& QVerbalExpressions::range(const std::initializer_list<QString> & args)
{
}
#endif

bool QVerbalExpressions::test(const QString& value)
{
    /// TODO
    QString toTest;
    if (modifiers & MULTILINE)
        toTest = value;
    else
        toTest = reduceLines(value);

    if (modifiers & GLOBAL)
        return toTest.contains(QRegExp(pattern /* XXX */ ));
    else
        return toTest.contains(QRegExp(pattern /* XXX */ ));
}

const QString QVerbalExpressions::replace(const QString& source, const QString& value)
{
}
