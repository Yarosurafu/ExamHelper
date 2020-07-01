#ifndef TESTS_H
#define TESTS_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class Tests;
}

class Tests : public QWidget
{
    Q_OBJECT

public:
    explicit Tests(const QJsonArray questions, QWidget *parent = nullptr);
    ~Tests();

private:
    QJsonArray questions;
    int currentQuestion = 0;
    Ui::Tests *ui;
private slots:
    void setQuestion();
};

#endif // TESTS_H
