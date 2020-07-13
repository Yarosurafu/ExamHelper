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
