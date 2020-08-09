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
    explicit Statistics(QWidget *parent = nullptr);
    void setData(const int correctAnswers, const int max);
    ~Statistics();

private:
    Ui::Statistics *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse = nullptr;
    QGraphicsEllipseItem *center = nullptr;
signals:
    void closeAll();
    void repeat();
private slots:
    void on_closeButton_clicked();
    void on_repeatButton_clicked();
};

#endif // STATISTICS_H
