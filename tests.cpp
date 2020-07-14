﻿#include "tests.h"
#include "ui_tests.h"
#include "nfcreator.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>

Tests::Tests(const QJsonArray questions, Statistics* statWindwow, QWidget *parent) :
    QWidget(parent),
    questions(questions),    
    statWindow(statWindwow),
    ui(new Ui::Tests)
{
    ui->setupUi(this);    
    answerButtons[0] = ui->firstAnsw;
    answerButtons[1] = ui->secondAnsw;
    answerButtons[2] = ui->thirdAnsw;
    answerButtons[3] = ui->fourthAnsw;
    answerButtons[4] = ui->fifthAnsw;
    setQuestion();
    connect(ui->nextQuestBut, SIGNAL(clicked()), this, SLOT(setQuestion()));
    connect(ui->firstAnsw, SIGNAL(clicked()), this, SLOT(checkAnswer()));
    connect(ui->secondAnsw, SIGNAL(clicked()), this, SLOT(checkAnswer()));
    connect(ui->thirdAnsw, SIGNAL(clicked()), this, SLOT(checkAnswer()));
    connect(ui->fourthAnsw, SIGNAL(clicked()), this, SLOT(checkAnswer()));
    connect(ui->fifthAnsw, SIGNAL(clicked()), this, SLOT(checkAnswer()));
}

Tests::~Tests()
{
    delete ui;
}

void Tests::setQuestion(){
    if(!isAnswered){
        QMessageBox::critical(this, "Ошибка", "Ответ не был выбран");
        return;
    }
    if(currentQuestion < 29){
        ++currentQuestion;
        ui->progressBar->setValue(currentQuestion);
    }
    else{
        statWindow->setData(correctAnswers);
        emit testEnd();
        return;
    }

    isAnswered = false;
    //Changing buttons theme to "base"
    for(int i = 0; i < 5; ++i)
        answerButtons[i]->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.884615, y2:0.892, stop:0 rgba(85, 170, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 85, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    //Changing question and answers
    QJsonObject question = questions[currentQuestion].toObject();
    ui->questionText->setText(question["question"].toString());
    QJsonArray answers = question["answers"].toArray();
    //TODO: DELETE THE '*'!!!
    for(int i = 0; i < answers.size(); ++i){
        answerButtons[i]->setText(answers[i].toString());
        if(answers[i].toString().contains("*"))
            currCorrectAnsw = answers[i].toString();
    }
    if(currentQuestion == 29)
        ui->nextQuestBut->setText("Завершить тест");
}

void Tests::checkAnswer(){
    if(isAnswered)
        return;
    QPushButton *userAnswButt = static_cast<QPushButton*>(sender());
    QString userAnsw = userAnswButt->text();

    if(userAnsw == currCorrectAnsw){
        userAnswButt->setStyleSheet("QPushButton{	\n	color: rgb(0, 85, 0);\n	background-color: rgb(85, 255, 127);\n	border: 4px solid rgb(0, 170, 0);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
        ++correctAnswers;
        isAnswered = true;
        return;
    }
    else{
        userAnswButt->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: rgb(255, 93, 93);\n	border: 4px solid rgb(170, 0, 0);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
        for(int i = 0; i < 5; ++i)
            if(answerButtons[i]->text() == currCorrectAnsw)
                answerButtons[i]->setStyleSheet("QPushButton{	\n	color: rgb(0, 85, 0);\n	background-color: rgb(85, 255, 127);\n	border: 4px solid rgb(0, 170, 0);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
        isAnswered = true;
    }
}

void Tests::on_setReminderBut_clicked()
{
    QJsonObject question = questions[currentQuestion].toObject();
    emit notification(question["question"].toString());
}
