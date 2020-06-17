#include "parsingprogress.h"
#include "ui_parsingprogress.h"

ParsingProgress::ParsingProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParsingProgress)
{
    ui->setupUi(this);
}

ParsingProgress::~ParsingProgress()
{
    delete ui;
}

void ParsingProgress::setProgressMin(const int min){
    ui->progressBar->setMinimum(min);
}

void ParsingProgress::setProgressMax(const int max){
    ui->progressBar->setMaximum(max);
}

void ParsingProgress::setProgress(const int progress){
    ui->progressBar->setValue(progress);
}

void ParsingProgress::resetProgress(){
    ui->progressBar->reset();
}
