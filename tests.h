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

    enum class Results{
        CORRECT_RESULT,
        WRONG_RESULT,
        PASSED_RESULT,
        FAILED_RESULT,
        PERFECT_RESULT,
        CHANGE_RESULT
    };

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

    void on_setReminderBut_clicked();

    void on_more_1_clicked();

    void on_more_2_clicked();

    void on_more_3_clicked();

    void on_more_4_clicked();

    void on_more_5_clicked();

signals:
    void testEnd();
    void notification(QJsonObject question);
    void answer(int result);
};

#endif // TESTS_H
