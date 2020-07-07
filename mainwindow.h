#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_parseButt_clicked();

    void on_pickFileButt_clicked();

    void on_searchButton_clicked();

    void on_nextButton_clicked();

    void on_prevButton_clicked();

    void on_startTest_clicked();

public slots:

    void setSubWindow(QWidget* widget, QString title);

private:
    Ui::MainWindow *ui;
    DataBase db_m;
    QJsonArray searchedQuestions_m;
    int currentQuestionInd;
    void setSearchedQuestion();
};
#endif // MAINWINDOW_H
