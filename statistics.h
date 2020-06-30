#ifndef STATISTICS_H
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
    explicit Statistics(int correctAnswQuantity, QWidget *parent = nullptr);
    ~Statistics();

private:
    Ui::Statistics *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
};

#endif // STATISTICS_H
