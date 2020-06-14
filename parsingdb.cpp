﻿#include "parsingdb.h"
#include "QFile"
#include "QJsonObject"
#include "QByteArray"
#include "QJsonDocument"
#include "QTextStream"
#include "QJsonArray"

ParsingDB::ParsingDB()
{

}

/**
 * @brief ParsingDB::parse
 *
 * Adding to the existing database of exam questions
 * new questions from HTML-files
 *
 * @param path Path to the HTML-file
 */
void ParsingDB::parse(const QString path){
    //----------Opening JSON-file----------
    QFile loadFile(":/database/test.json");
    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Cannot open JSON-file");
        return;
    }
    QByteArray data = loadFile.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject database = doc.object();
    QJsonArray questions = database["questions"].toArray();
    //-------------------------------------

    //----------Opening HTML-file----------
    QFile html(path);
    if(!html.open(QIODevice::ReadOnly)){
        qWarning("Cannot open HTML-file");
        return;
    }
    QTextStream in(&html);
    //-------------------------------------

    //-------------Parsing-----------------
    while(!in.atEnd()){
        QString line = in.readLine();
        //Checking subject and subject matter
        if(line.contains("<h1 class=\"text-center\">")){
            line.remove("<h1 class=\"text-center\">");
            line.remove("</h1>");
            line.remove("\t");
            //Now line is a current subject matter
            QJsonObject currMatter;
            QJsonArray currMatterQuestions;
            int matterInd = indexOfElement(questions, line);
            //If DB already has current subject matter
            if(matterInd >= 0){
                currMatter = questions[matterInd].toObject();
                currMatterQuestions = currMatter["questions"].toArray();
            }
            //-----Getting question-----
            QString question;
            for(size_t i = 0; i < 3; ++i)
                question = in.readLine();
            question.remove("<h4><b>");
            question.remove("</b>");
            question.remove("<ul>");
            QString buff = question.chopped((question.size() - 14));
            question.remove(buff);
            //--------------------------

            //------Getting answers-----
            QJsonArray answers;
            for(int i = 0; i < 5; ++i){
                QString answer;
                do{
                    answer = in.readLine();
                    answer.remove("\t");
                } while(answer.contains("</li>") || answer == "");

                //If answer is correct
                if(answer.contains("<li class=\"list-group-item\" style=\"background-color:#C6FFCD;border:0px none;\">")){
                    answer = in.readLine();
                    answer.append("*");
                }
                else if(answer.contains("<li class=\"list-group-item\" style=\";border:0px none;\">"))
                    answer = in.readLine();
                answer.remove("\t");
                answers.append(answer);
            }
            //--------------------------

            //Creating question with the answers
            QJsonObject fullQuestion = {
                {"question", question},
                {"answers", answers}
            };

            //Saving
            QFile saveFile("C:/DOSGames/test.json");
            if(!saveFile.open(QIODevice::WriteOnly)){
                qWarning("Cannot open save JSON");
                return;
            }
            currMatterQuestions.append(fullQuestion);
            QJsonObject newSubject = {
                {"subject", line},
                {"questions", currMatterQuestions}
            };
            if(matterInd >= 0){
                questions[matterInd] = newSubject;
            }
            else{
                questions.append(newSubject);
            }
            database["questions"] = questions;
            saveFile.write(QJsonDocument(database).toJson());
            saveFile.close();
        }
    }
    //-------------End loop----------------
}

/**
 * @brief ParsingDB::indexOfElement
 *
 * Searching an index of element
 *
 * @param array
 * @param element
 * @return index of element or -1 if array
 * does not contain an element
 */
int ParsingDB::indexOfElement(QJsonArray array, const QString element){
    for(size_t i = 0; i < array.size(); ++i){
        QJsonObject subject = array.at(i).toObject();
        if(subject["subject"] == element)
            return i;
    }
    return -1;
}
