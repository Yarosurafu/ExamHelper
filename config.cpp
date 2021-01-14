#include "config.h"
#include <QFile>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Config::Config()
{
    parseOptions();
}

void Config::parseOptions(){
    //----------Opening JSON-file----------
    QString filePath = QApplication::applicationDirPath();
    QFile loadFile(filePath + "/database/config.json");
    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Cannot open JSON-file");
        return;
    }
    QByteArray data = loadFile.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    options = doc.array();
    loadFile.close();
    //-------------------------------------
}

std::vector<QString> Config::getButtons(){
    std::vector<QString> buttons;
    QJsonObject buttonOpt = getOption("buttons");
    if(buttonOpt.empty()) return buttons;
    buttons.push_back(buttonOpt["first"].toString());
    buttons.push_back(buttonOpt["second"].toString());
    buttons.push_back(buttonOpt["third"].toString());
    return buttons;
}

QJsonObject Config::getOption(QString option){
    for(int i = 0; i < options.size(); ++i)
        if((options.at(i).toObject())["option"] == option)
            return options.at(i).toObject();
    return QJsonObject();
}

void Config::saveOptions(std::vector<QString> buttons){
    //Saving
    QString filePath = QApplication::applicationDirPath();
    QFile saveFile(filePath + "/database/config.json");
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qWarning("Cannot open save JSON");
        return;
    }
    QJsonObject newButtons = {
        {"option", "buttons"},
        {"first", buttons.at(0)},
        {"second", buttons.at(1)},
        {"third", buttons.at(2)}
    };
    QJsonArray finalOptions;
    finalOptions.push_back(newButtons);
    saveFile.write(QJsonDocument(finalOptions).toJson());
    saveFile.close();
}
