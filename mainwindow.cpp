#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parsingdb.h"
#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_parseButt_clicked()
{
    ParsingDB::parse("C:/Users/yarik/Downloads/1.html");
}
