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
    ui->twelveHNotif->setCheckable(true);
    ui->oneDayNotif->setCheckable(true);
    ui->threeDaysNotif->setCheckable(true);
    ui->twelveHNotif->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.841346, y2:0.756, stop:0 rgba(170, 0, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 0, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    ui->oneDayNotif->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.841346, y2:0.756, stop:0 rgba(170, 0, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 0, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    ui->threeDaysNotif->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.841346, y2:0.756, stop:0 rgba(170, 0, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 0, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");

    connect(ui->twelveHNotif, &QPushButton::clicked, this, &NfCreator::on_hours_clicked);
    connect(ui->oneDayNotif, &QPushButton::clicked, this, &NfCreator::on_hours_clicked);
    connect(ui->threeDaysNotif, &QPushButton::clicked, this, &NfCreator::on_hours_clicked);
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
    QString time = ui->timeEdit->text().replace(":", "-");
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
    int year{}, month{}, day{};
    QDate chosenDate;
    QString timeS;
    if(ui->twelveHNotif->isChecked()){
        QDateTime nextDateTime = QDateTime::currentDateTime().addSecs(43200);
        chosenDate = nextDateTime.date();
        timeS = nextDateTime.time().toString();
        ui->twelveHNotif->setChecked(false);
    }
    else if(ui->oneDayNotif->isChecked()){
        QDateTime nextDateTime = QDateTime::currentDateTime().addDays(1);
        chosenDate = nextDateTime.date();
        timeS = nextDateTime.time().toString();
        ui->oneDayNotif->setChecked(false);
    }
    else if(ui->threeDaysNotif->isChecked()){
        QDateTime nextDateTime = QDateTime::currentDateTime().addDays(3);
        chosenDate = nextDateTime.date();
        timeS = nextDateTime.time().toString();
        ui->threeDaysNotif->setChecked(false);
    }
    else{
        chosenDate = ui->calendar->selectedDate();
        timeS = ui->timeEdit->text();
    }
    year = chosenDate.year();
    month = chosenDate.month();
    day = chosenDate.day();
    QString dayS = QString::number(day);
    QString monthS = QString::number(month);
    if(dayS.length() == 1)
        dayS = "0" + dayS;
    if(monthS.length() == 1)
        monthS = "0" + monthS;
    if(timeS.length() == 4)
        timeS = "0" + timeS;
    if(timeS.length() > 5)
        timeS.remove(5, 3);
    //--------------------------------

    m_date = "/tn exam-" + QString::number(day) + "-"
            + QString::number(month) + "-" + QString::number(year) + "-"
            + timeS.replace(":", "-");
    timeS.replace("-", ":");

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
    qDebug() << command;
    QByteArray ba = command.toLatin1();
    const char *c_str = ba.data();
    system(c_str);
    delete c_str;
}

void NfCreator::on_hours_clicked(){
    if(ui->twelveHNotif->isChecked()){
        ui->twelveHNotif->setChecked(false);
        ui->twelveHNotif->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.841346, y2:0.756, stop:0 rgba(170, 0, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 0, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    }
    if(ui->oneDayNotif->isChecked()){
        ui->oneDayNotif->setChecked(false);
        ui->oneDayNotif->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.841346, y2:0.756, stop:0 rgba(170, 0, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 0, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    }
    if(ui->threeDaysNotif->isChecked()){
        ui->threeDaysNotif->setChecked(false);
        ui->threeDaysNotif->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.841346, y2:0.756, stop:0 rgba(170, 0, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 0, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    }
    QPushButton* button = static_cast<QPushButton*>(sender());
    button->setChecked(true);
    button->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 0, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
}
