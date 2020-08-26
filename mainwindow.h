#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "database.h"
#include "notification.h"
#include "config.h"

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

    void setSubWindow(QWidget* widget, QString title, QMdiArea* area);

    void on_startDownload_clicked();

    void setBasya(int emotion);

    void on_refreshNotif_clicked();

    void on_startNotif_clicked();

    void on_applyButton_clicked();

    void on_applyQuest_clicked();

private:
    Ui::MainWindow *ui;
    DataBase db_m;
    Notification notif;
    Config conf;
    QJsonArray searchedQuestions_m;
    int questionQuantity = 20;
    int currentQuestionInd;
    void setSearchedQuestion();
};
#endif // MAINWINDOW_H
