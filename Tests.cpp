
#include <QDebug>

#include "QVerbalExpressions.h"



int main(int argc, char **argv)
{
    {
        auto expression = QVerbalExpressions()
            .searchOneLine()
            .startOfLine()
            .then("http")
            .maybe("s")
            .then("://")
            .maybe("www.")
            .anythingBut(" ")
            .endOfLine();

        qDebug() << expression.test("https://www.google.com");
    }

    {
        QString replaceMe = "Replace bird with a duck";

        auto expression = QVerbalExpressions()
            .find("bird");

        qDebug() << expression.replace(replaceMe, "duck");
    }


    return 0;
}
