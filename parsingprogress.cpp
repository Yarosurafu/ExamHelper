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
