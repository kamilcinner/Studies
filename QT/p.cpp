#include "wykres.h"
#include "ui_wykres.h"

Wykres::Wykres(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wykres)
{
    ui->setupUi(this);
    ui->grafika->setScene(&scene);
    setPens();
    generateRandomPoints();
}

Wykres::~Wykres()
{
    delete ui;
}

void Wykres::setPens() {
    bluePen.setColor(Qt::blue);
    bluePen.setWidth(1);
    blackPen.setColor(Qt::black);
    blackPen.setWidth(1);
}

void Wykres::addPoint(int x, int y) {
    QPoint newPoint(x, y);
    if (pointList.size() == 0) {
        pointList.append(newPoint);
        return;
    }
    scene.addLine(pointList.back().x(), pointList.back().y(), x, y, bluePen);
    pointList.append(newPoint);
}

void Wykres::generateRandomPoints() {
    QRandomGenerator generator;
    int x, y;
    for (int i = 0; i < 100; i++) {
        x = generator.bounded(0, 500);
        y = generator.bounded(0, 500);
        if (pointList.size() == 0 || x > pointList.back().x())
            addPoint(x, y);
        else i--;
    }
}
