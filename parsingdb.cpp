#include "parsingdb.h"
#include "QFile"
#include "QJsonObject"
#include "QByteArray"
#include "QJsonDocument"
#include "QTextStream"

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
    //-------------------------------------

    //----------Opening HTML-file----------
    QFile html(path);
    if(!html.open(QIODevice::ReadOnly)){
        qWarning("Cannot open HTML-file");
        return;
    }
    //-------------------------------------

    //-------------Parsing-----------------
    QTextStream
    //-------------------------------------
}
