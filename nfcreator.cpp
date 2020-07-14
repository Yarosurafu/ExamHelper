#include "nfcreator.h"
#include "ui_nfcreator.h"

NfCreator::NfCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NfCreator)
{
    ui->setupUi(this);
}

NfCreator::~NfCreator()
{
    delete ui;
}

void NfCreator::setQuestion(QString questionArg){
    question = questionArg;
}

void NfCreator::on_pushButton_5_clicked()
{
    this->close();
}
