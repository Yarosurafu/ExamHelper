#ifndef DATABASE_H
#define DATABASE_H
#include <QJsonArray>
#include <vector>
#include <QString>

class DataBase
{
    QJsonArray subjects_m;
    std::vector<QString> subjectsNames_m;

public:
    DataBase();
    std::vector<QString> getSubjectsNames(){
        return subjectsNames_m;
    }
    QJsonArray searchQuestion(const QString matter, const QString key);
};

#endif // DATABASE_H
