#include "nfcreator.h"
#include "ui_nfcreator.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextCodec>

NfCreator::NfCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NfCreator)
{
    ui->setupUi(this);
}

NfCreator::~NfCreator()
{
    delete ui;
}

void NfCreator::setQuestion(QString questionArg){
    m_question = questionArg;
    qDebug() << m_question << "\n";
}

void NfCreator::on_cancelBut_clicked()
{
    emit exit();
}

void NfCreator::on_createNotifBut_clicked()
{
    QDate chosenDate = ui->calendar->selectedDate();
    int year = chosenDate.year();
    int month = chosenDate.month();
    int day = chosenDate.day();
    m_date = "/sd " + QString::number(day) + "/" + QString::number(month) + "/"
            + QString::number(year) + " /st " + ui->timeEdit->text() + " /st once";
    writeToJson();
    emit exit();
}

void NfCreator::writeToJson(){
    QString path = QApplication::applicationDirPath()+ "/database/notifications.json";
    qDebug() << path;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning("Cannot open JSON-file");
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument document(QJsonDocument::fromJson(data));
    QJsonObject database = document.object();
    QJsonArray notifications = database["notifications"].toArray();

    QJsonObject newNotif = {
      {"date", m_date},
      {"question", m_question}
    };

    notifications.append(newNotif);
    database["notifications"] = notifications;
    QFile saveFile(path);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qWarning("Cannot open save JSON");
        return;
    }
    saveFile.write(QJsonDocument(database).toJson());
    saveFile.close();
}
