#include "notification.h"
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDate>
#include <QDateTime>
#include <QTime>

Notification::Notification()
{
    update();
}

void Notification::update(){
    parseJson();
    formCurrentQuestions();
}

void Notification::parseJson(){
    QFile loadFile(QApplication::applicationDirPath() + "/database/notifications.json");
    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning() << "Cannot open json\n";
        return;
    }
    QByteArray data = loadFile.readAll();
    loadFile.close();
    QJsonDocument db(QJsonDocument::fromJson(data));
    database = (db.object())["notifications"].toArray();
}

void Notification::formCurrentQuestions(){
    questions.clear();
    //Getting current Date and Time for checking notifications
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();
    QJsonObject currentQuestion;
     for(int i = 0; i < database.size(); ++i){
        currentQuestion = database[i].toObject();
        //-----Getting date and time of notification-----
        int minutes = currentQuestion["time"].toString().remove(0, 3).toInt();
        int hours = currentQuestion["time"].toString().remove(2, 3).toInt();
        int year = currentQuestion["year"].toString().toInt();
        int month = currentQuestion["month"].toString().toInt();
        int day = currentQuestion["day"].toString().toInt();
        QDate notifDate(year, month, day);
        QTime notifTime(hours, minutes);
        //-----------------------------------------------

        //If date and time of current question are less than current time
        //and date - then adding an index of current question to the array
        if(notifDate <= currentDate && notifTime <= currentTime){
            questions.push_back(i);
        }
    }
}

void Notification::deleteCurrentQuestionsFromFile(){
    //-----Removing outdated questions-----
    QJsonArray buff = database;
    for(size_t i = 0; i < questions.size(); ++i){
        for(int j = 0; j < database.size(); ++j)
            if(buff.at(questions[i]) == database.at(j)){
                database.removeAt(j);
                break;
            }
    }
    //-------------------------------------

    //---Saving updated database to JSON---
    QFile saveFile(QApplication::applicationDirPath() + "/database/notifications.json");
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qWarning("Cannot open save JSON");
        return;
    }
    QJsonObject finalBase = {{"notifications", database}};
    saveFile.write(QJsonDocument(finalBase).toJson());
    saveFile.close();
    //-------------------------------------
}

QJsonArray Notification::getQuestions(){
    QJsonArray variant;
    for(size_t i = 0; i < questions.size(); ++i)
        variant.append(database.at(questions[i]));
    return variant;
}

int Notification::getNotifQuant(){
    return questions.size();
}
