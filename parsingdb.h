#ifndef PARSINGDB_H
#define PARSINGDB_H
#include "QString"
#include "QJsonArray"

class ParsingDB
{
public:
    ParsingDB();
    static void parse(const QString path);
private:
    static int indexOfElement(QJsonArray array, const QString element);
    static void parseBooklet(const QString path);
    static void parseTests(const QString path);
};

#endif // PARSINGDB_H
