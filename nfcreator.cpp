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

void NfCreator::setQuestion(QJsonObject questionArg){
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
    QString time = ui->timeEdit->text().replace(":", "-");
    m_date = "/tn exam-" + QString::number(day) + "-"
            + QString::number(month) + "-" + QString::number(year) + "-"
            + time;
    writeToJson();
    emit exit();
}

void NfCreator::writeToJson(){
    //----------Opening file----------
    QString path = QApplication::applicationDirPath()+ "/database/notifications.json";
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
    //--------------------------------

    //--Picking date and question with answers--
    QDate chosenDate = ui->calendar->selectedDate();
    int year = chosenDate.year();
    int month = chosenDate.month();
    int day = chosenDate.day();
    QString dayS = QString::number(day);
    QString monthS = QString::number(month);
    QString timeS = ui->timeEdit->text();
    if(dayS.length() == 1)
        dayS = "0" + dayS;
    if(monthS.length() == 1)
        monthS = "0" + monthS;
    if(timeS.length() == 4)
        timeS = "0" + timeS;
    //--------------------------------

    QJsonObject newNotif = {
        {"name", m_date},
        {"question", m_question["question"].toString()},
        {"answers", m_question["answers"].toArray()},
        {"day", dayS},
        {"month", monthS},
        {"year", QString::number(year)},
        {"time", timeS}
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
    m_date += " /tr \"" + QApplication::applicationDirPath() + "/NotificationHelper" + "\" /sd " + dayS + "/" + monthS + "/"
            + QString::number(year) + " /st " + timeS + " /sc once";
    QString command = "schtasks /create " + m_date;
    QMessageBox::about(this, "Debug", command);
    QByteArray ba = command.toLatin1();
    const char *c_str = ba.data();
    system(c_str);
    delete c_str;
}
