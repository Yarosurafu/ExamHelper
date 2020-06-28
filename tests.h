#ifndef TESTS_H
#define TESTS_H

#include <QWidget>

namespace Ui {
class Tests;
}

class Tests : public QWidget
{
    Q_OBJECT

public:
    explicit Tests(QWidget *parent = nullptr);
    ~Tests();

private:
    Ui::Tests *ui;
};

#endif // TESTS_H
