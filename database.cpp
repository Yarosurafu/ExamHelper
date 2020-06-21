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
}
