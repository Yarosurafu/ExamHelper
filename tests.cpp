#include "tests.h"
#include "ui_tests.h"
#include <QJsonObject>
#include <QJsonArray>

Tests::Tests(const QJsonArray questions, Statistics* statWindwow, QWidget *parent) :
    QWidget(parent),
    questions(questions),    
    statWindow(statWindwow),
    ui(new Ui::Tests)
{
    ui->setupUi(this);
    setQuestion();
    connect(ui->nextQuestBut, SIGNAL(clicked()), this, SLOT(setQuestion()));
}

Tests::~Tests()
{
    delete statWindow;
    delete ui;
}

void Tests::setQuestion(){
    if(currentQuestion < 29){
        ++currentQuestion;
        ui->progressBar->setValue(currentQuestion);
    }
    else{
        statWindow->setData(correctQuestions);
        emit testEnd();
        return;
    }
    //Changing buttons theme to "base"
    ui->firstAnsw->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.884615, y2:0.892, stop:0 rgba(85, 170, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 85, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    ui->secondAnsw->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.884615, y2:0.892, stop:0 rgba(85, 170, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 85, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    ui->thirdAnsw->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.884615, y2:0.892, stop:0 rgba(85, 170, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 85, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    ui->fourthAnsw->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.884615, y2:0.892, stop:0 rgba(85, 170, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 85, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    ui->fifthAnsw->setStyleSheet("QPushButton{	\n	color: black;\n	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.884615, y2:0.892, stop:0 rgba(85, 170, 255, 255), stop:1 rgba(255, 255, 255, 255));\n	border: 2px solid rgb(0, 85, 255);\n	padding: 6px;\n	border-radius: 20px 10px;\n}\n\nQPushButton:pressed{\n	color: red;\n	border: 4px solid red;\n	border-radius: 20px 10px;\n}");
    //Changing question and answers
    QJsonObject question = questions[currentQuestion].toObject();
    ui->questionText->setText(question["question"].toString());
    QJsonArray answers = question["answers"].toArray();
    ui->firstAnsw->setText(answers[0].toString());
    ui->secondAnsw->setText(answers[1].toString());
    ui->thirdAnsw->setText(answers[2].toString());
    ui->fourthAnsw->setText(answers[3].toString());
    ui->fifthAnsw->setText(answers[4].toString());
    if(currentQuestion == 29)
        ui->nextQuestBut->setText("Завершить тест");
}
