#ifndef PARSINGDB_H
#define PARSINGDB_H
#include "QString"

class ParsingDB
{
public:
    ParsingDB();
    static void parse(const QString path);
};

#endif // PARSINGDB_H
