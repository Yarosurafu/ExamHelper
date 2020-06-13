#include "parsingdb.h"
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
    if(!loadFile.open(QIODevice::ReadWrite)){
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
    if(!html.open(QIODevice::ReadOnly | QIODevice::Text)){
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
            //Now line is a current subject matter
            QJsonArray currMatter;
            //If DB already has current subject matter
            if(questions.contains(line)){
                int matterInd = indexOfElement(questions, line);
                currMatter = questions[matterInd].toArray();
            }
            //-----Getting question-----
            QString question;
            for(size_t i = 0; i < 3; ++i)
                question = in.readLine();
            question.remove("<h4><b>");
            question.remove("</b>");
            question.remove("<ul>");
            //--------------------------

            //------Getting answers-----
            QJsonArray answers;
            for(int i = 0; i < 5; ++i){
                QString answer;
                do{
                    answer = in.readLine();
                } while(answer == "</li>" || answer == "");
                //If answer is correct
                if(answer.contains("<li class=\"list-group-item\" style=\"background-color:#C6FFCD;border:0px none;\">")){
                    answer = in.readLine();
                    answer.append("*");
                }
                else if(answer.contains("<li class=\"list-group-item\" style=\";border:0px none;\">"))
                    answer = in.readLine();
                answers.append(answer);
            }
            //--------------------------

            //Creating question with the answers
            QJsonObject fullQuestion = {
                {"question", question},
                {"answers", answers}
            };

            //Saving
            currMatter.append(fullQuestion);
            if(questions.contains(line)){
                int matterInd = indexOfElement(questions, line);
                questions[matterInd] = currMatter;
            }
            database["questions"] = questions;
            loadFile.write(QJsonDocument(database).toJson());
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
    for(size_t i = 0; i < array.size(); ++i)
        if(array.at(i) == element)
            return i;
    return -1;
}
