﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parsingdb.h"
#include "parsingprogress.h"
#include "database.h"

#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>
#include <chrono>
#include <thread>
#include <vector>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::vector<QString> subjectsNames = db_m.getSubjectsNames();
    for(size_t i = 0; i < subjectsNames.size(); ++i)
        ui->matterComboBox->addItem(subjectsNames[i]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_parseButt_clicked()
{
    ParsingProgress progress(this);
    QString dirName = ui->directoryLine->text();
    ui->directoryLine->clear();
    QDir directory(dirName);
    QFileInfoList files = directory.entryInfoList();
    progress.setProgressMin(0);
    progress.setProgressMax(files.size());
    progress.show();
    for(int i = 0; i < files.size(); ++i){
        progress.setProgress(i);
        if(files[i].absoluteFilePath().contains(".html"))
            ParsingDB::parse(files[i].absoluteFilePath());
    }
    progress.hide();
    progress.resetProgress();
}

void MainWindow::on_pickFileButt_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, "Pick up directory with HTML", "C:/", QFileDialog::ShowDirsOnly
                                                                                                    | QFileDialog::DontResolveSymlinks);
    ui->directoryLine->setText(dirName);
}

void MainWindow::on_searchButton_clicked()
{
    QString key = ui->userQuestion->text();
    QString matter = ui->matterComboBox->currentText();
    searchedQuestions_m = db_m.searchQuestion(matter, key);
    currentQuestionInd = 0;
    QJsonObject currentQuestion = searchedQuestions_m[0].toObject();
    ui->fullQuestion->setText(currentQuestion["question"].toString());
    ui->answer->setText(currentQuestion["answer"].toString());
}
