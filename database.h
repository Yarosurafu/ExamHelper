#ifndef DATABASE_H
#define DATABASE_H
#include <QJsonArray>

class DataBase
{
    QJsonArray subjects_m;
public:
    DataBase();
    QString* getAllSubjects(const int* size);
};

#endif // DATABASE_H
