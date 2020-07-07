#include "statistics.h"
#include "ui_statistics.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

Statistics::Statistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
}

void Statistics::setData(const int correctAnswers){

    int angle = correctAnswers * 360 * 16 / 30;
    QPen blackPen(Qt::black);
    QPen whitePen(Qt::white);
    QBrush redBrush(Qt::red);
    QBrush whiteBrush(Qt::white);
    ellipse = new QGraphicsEllipseItem(-35, -37, 100, 100);
    ellipse->setPen(whitePen);
    ellipse->setBrush(redBrush);
    ellipse->setSpanAngle(angle);
    ellipse->setStartAngle(1440);
    scene->addItem(ellipse);
    center = new QGraphicsEllipseItem(-10, -12, 50, 50);
    center->setPen(whitePen);
    center->setBrush(whiteBrush);
    center->setSpanAngle(angle);
    center->setStartAngle(1440);
    scene->addItem(center);
    scene->addText(QString::number(correctAnswers * 100 / 30) + "%");
    ui->statView->setScene(scene);
    ui->correctQuant->setText(QString::number(correctAnswers));
    ui->incorrectQuant->setText(QString::number(30 - correctAnswers));
    ui->statView->repaint();
}

Statistics::~Statistics()
{
    delete ellipse;
    delete center;
    delete scene;
    delete ui;
}

void Statistics::on_closeButton_clicked()
{
    emit closeAll();
}

void Statistics::on_repeatButton_clicked()
{
    emit repeat();
}
