﻿#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

namespace Ui {
class Statistics;
}

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    void setData(const int correctAnswers);
    ~Statistics();

private:
    Ui::Statistics *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse = nullptr;
    QGraphicsEllipseItem *center = nullptr;
};

#endif // STATISTICS_H
