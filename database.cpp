#include "database.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QApplication>
#include <QJsonObject>

DataBase::DataBase()
{
    QString filePath = QApplication::applicationDirPath();
    QFile loadFile(filePath + "/database/test.json");
    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Error opening JSON-file");
        return;
    }
    QByteArray data = loadFile.readAll();
    loadFile.close();
    QJsonDocument db(QJsonDocument::fromJson(data));
    QJsonObject buff = db.object();
    subjects_m = buff["questions"].toArray();

    //-----subjectsNames_m init-----
    for(size_t i = 0; i < subjects_m.size(); ++i){
        QJsonObject currentSubj = subjects_m[i].toObject();
        subjectsNames_m.push_back(currentSubj["subject"].toString());
    }
}

QJsonObject DataBase::searchQuestion(const QString matter, const QString key){
    QJsonObject currMatter;
    for(int i = 0; i < subjects_m.size(); ++i){
        currMatter = subjects_m[i].toObject();
        if(currMatter["subject"].toString() == matter)
            break;
        else if(i == subjects_m.size()){
            currMatter = {
                    {"questions", ""},
                    {"subject", ""}
                };
            return currMatter;
        }
    }
}
