#ifndef TESTS_H
#define TESTS_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QPushButton>
#include "statistics.h"

namespace Ui {
class Tests;
}

class Tests : public QWidget
{
    Q_OBJECT

public:
    explicit Tests(const QJsonArray questions, Statistics* statWindwow, QWidget *parent = nullptr);
    ~Tests();

private:
    QJsonArray questions;
    int currentQuestion = -1;
    int correctAnswers = 0;
    Statistics* statWindow;
    Ui::Tests *ui;
    QPushButton *answerButtons[5];
    QString currCorrectAnsw;
    bool isAnswered = true;
    bool checkButtons();
private slots:
    void setQuestion();
    void checkAnswer();
signals:
    void testEnd();
};

#endif // TESTS_H
