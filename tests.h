#ifndef TESTS_H
#define TESTS_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
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
    int currentQuestion = 0;
    int correctQuestions = 26;
    Statistics* statWindow;
    Ui::Tests *ui;
private slots:
    void setQuestion();
signals:
    void testEnd();
};

#endif // TESTS_H
