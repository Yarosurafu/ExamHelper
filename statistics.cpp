#include "statistics.h"
#include "ui_statistics.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

Statistics::Statistics(int correctAnswQuant, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistics)
{
    int angle = correctAnswQuant * 360 * 16 / 30;
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    QPen blackPen(Qt::black);
    QPen whitePen(Qt::white);
    QBrush redBrush(Qt::red);
    QBrush whiteBrush(Qt::white);
    ellipse = scene->addEllipse(-35, -37, 100, 100, whitePen, redBrush);
    ellipse->setSpanAngle(angle);
    ellipse->setStartAngle(1440);
    QGraphicsEllipseItem* center = scene->addEllipse(-10, -12, 50, 50, whitePen, whiteBrush);
    center->setSpanAngle(angle);
    center->setStartAngle(1440);
    scene->setFocusItem(ellipse);
    scene->addText(QString::number(correctAnswQuant * 100 / 30) + "%");
    ui->statView->setScene(scene);
}

Statistics::~Statistics()
{
    delete ui;
}
