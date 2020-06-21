#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parsingdb.h"
#include "parsingprogress.h"

#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>
#include <chrono>
#include <thread>

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
