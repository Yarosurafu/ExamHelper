﻿#include "database.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QApplication>
#include <QJsonObject>
#include <random>

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
    for(int i = 0; i < subjects_m.size(); ++i){
        QJsonObject currentSubj = subjects_m[i].toObject();
        subjectsNames_m.push_back(currentSubj["subject"].toString());
    }
}

/**
 * @brief DataBase::searchQuestion
 * Searching questions of the
 * matter in database by the key
 *
 * @param matter
 * @param key
 * @return questions An array of
 * questions or an array with one
 * object - nullQuestions, which means
 * empty question.
 */
QJsonArray DataBase::searchQuestion(const QString matter, const QString key){
    QJsonArray matters;
    QJsonObject currMatter;
    QJsonArray questions;
    //----------Searching key-matter----------
    for(int i = 0; i < subjects_m.size(); ++i){
        if(matter == "Искать во всех темах"){
            break;
        }
        currMatter = subjects_m[i].toObject();
        if(currMatter["subject"].toString() == matter)
            break;
        else if(i == subjects_m.size()){
            QJsonObject nullQuestion = {
                {"question", ""},
                {"answer", ""}
            };
            questions.append(nullQuestion);
            return questions;
        }
    }
    //----------------------------------------

    //------Searching questions by the key----
    for(int i = 0; i < subjects_m.size(); ++i){
        if(matter == "Искать во всех темах")
            currMatter = subjects_m[i].toObject();
        QJsonArray allQuestions = currMatter["questions"].toArray();
        QJsonObject question;
        for(int i = 0; i < allQuestions.size(); ++i){
            question = allQuestions[i].toObject();
            //Continue if current questions doesn't contain a key-word or phrase
            if(!question["question"].toString().contains(key, Qt::CaseInsensitive))
                continue;
            //Searching true answer to the current question
            QJsonArray questionAnswers = question["answers"].toArray();
            for(int j = 0; j < questionAnswers.size(); ++j)
                if(questionAnswers[j].toString().contains("*")){
                    question = {
                        {"question", question["question"].toString()},
                        {"answer", questionAnswers[j].toString()}
                    };
                    questions.append(question);
                }
        }
        if(matter != "Искать во всех темах")
            break;
    }
    //----------------------------------------
    return questions;
}

//TODO: finish method. Now it's just buffer
QJsonArray DataBase::getTestVariant(const QString matter, const int quantity){
    QJsonObject subject;
    for(int i = 0; i < subjects_m.size(); ++i){
        subject = subjects_m[i].toObject();
        if(subject["subject"].toString() == matter)
            break;
    }
    QJsonArray allQuestions = subject["questions"].toArray();
    QJsonArray variant;
    std::mt19937 mersenne(time(0));
    std::uniform_int_distribution<> distrib(0, allQuestions.size() - 1);
    for(int i = 0; i < quantity; ++i){
        variant.push_back(allQuestions[distrib(mersenne)]);
    }
    return variant;
}
