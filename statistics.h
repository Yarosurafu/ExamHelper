#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>

namespace Ui {
class Statistics;
}

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    ~Statistics();

private:
    Ui::Statistics *ui;
};

#endif // STATISTICS_H
