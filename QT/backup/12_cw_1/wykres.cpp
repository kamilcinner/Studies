#include "wykres.h"
#include "ui_wykres.h"

Wykres::Wykres(QWidget *parent) : QWidget(parent), ui(new Ui::Wykres) {
    ui->setupUi(this);
    ui->grafika->setScene(&scene);
    setStartValues();
    setPens();
}

Wykres::~Wykres() { delete ui; }

void Wykres::setStartValues() {
    plotsNumber = 20;
    graphType = line;
    maxY = minY = maxX = minX = baseMaxY = baseMinY = baseMaxX = baseMinX = 0;
    scalingParam = 1;
    ui->toLineButton->setEnabled(false);
    ui->toPointButton->setEnabled(true);
    ui->clearFieldButton->setEnabled(false);
    ui->enlargeButton->setEnabled(false);
    ui->decreaseButton->setEnabled(false);
    ui->drawNewGraphButton->setEnabled(true);
}

void Wykres::setPens() {
    graphColor.append(Qt::blue);
    graphColor.append(Qt::red);
    graphColor.append(Qt::green);
    graphColor.append(Qt::yellow);
    graphColor.append(Qt::magenta);
    graphPen.setWidth(1);
    axisPen.setColor(Qt::black);
    axisPen.setWidth(1);
}

void Wykres::addPoint(QList<QPoint> &pList, int x, int y) {
    if (y > maxY) baseMaxY = maxY = y;
    if (y < minY) baseMinY = minY = y;
    if (pList.size() == 0) {
        pList.append(*(new QPoint(x, y)));
        return;
    }
    bool isSet = false;
    for (int i = 0; i < pList.size(); i++)
        if (x < pList.at(i).x()) {
            pList.insert(i, *(new QPoint(x, y)));
            isSet = true;
            break;
        }
    if (!isSet)
        pList.append(*(new QPoint(x, y)));
}

void Wykres::generateRandomPoints() {
    QList<QPoint> pList;
    int x, y;
    bool sameX;
    for (int i = 0; i < 100; i++) {
        sameX = false;
        x = generator.bounded(-500, 500);
        y = generator.bounded(-250, 250);
        for (int j = 0; j < i; j++)
            if (x == pList.at(j).x())
                sameX = true;
        if(sameX) i--;
        else addPoint(pList, x, y);
    }
    if (pList.front().x() < minX) baseMinX = minX = pList.front().x();
    if (pList.back().x() > maxX) baseMaxX = maxX = pList.back().x();
    pointList.append(pList);
    typeList.append(graphType);
}

void Wykres::drawGraph(const int &graphIndex) {
    switch (typeList[graphIndex]) {
    case line:
        int x1, y1, x2, y2;
        for (int i = 1; i < pointList[graphIndex].size(); i++) {
            x1 = static_cast<int>(pointList[graphIndex].at(i - 1).x() * scalingParam);
            y1 = static_cast<int>(pointList[graphIndex].at(i - 1).y() * scalingParam);
            x2 = static_cast<int>(pointList[graphIndex].at(i).x() * scalingParam);
            y2 = static_cast<int>(pointList[graphIndex].at(i).y() * scalingParam);
            scene.addLine(x1, y1, x2, y2, graphPen);
        }
        break;
    case point:
        int x, y;
        for (int i = 0; i <pointList[graphIndex].size(); i++) {
            x = static_cast<int>(pointList[graphIndex].at(i).x() * scalingParam);
            y = static_cast<int>(pointList[graphIndex].at(i).y() * scalingParam);
            scene.addEllipse(x - 2, y - 2, 4, 4, graphPen);
        }
        break;
    }
}

void Wykres::drawXaxis() {
    QGraphicsTextItem *text;
    scene.addLine(minX - 100, 0, maxX + 100, 0, axisPen);
    text = scene.addText("osX[-]");
    text->setPos(maxX + 105, - 12);
}

void Wykres::drawYaxis() {
    QGraphicsTextItem *text;
    scene.addLine(0, minY - 100, 0, maxY + 100, axisPen);
    text = scene.addText("osY[-]");
    text->setPos(- 18, minY - 125);
}

void Wykres::drawScale() {
    QGraphicsTextItem *text;
    int xPlot = (maxX + qAbs<int>(minX)) / plotsNumber;
    int yPlot = (maxY + qAbs<int>(minY)) / plotsNumber;
    int baseXPlot = (baseMaxX + qAbs<int>(baseMinX)) / plotsNumber;
    int baseYPlot = (baseMaxY + qAbs<int>(baseMinY)) / plotsNumber;
    int i = 1;
    // X-axis
    while (i * xPlot <= maxX + 100) {
        scene.addLine(i * xPlot, 5, i * xPlot, - 5, axisPen);
        text = scene.addText(QString::number(i * baseXPlot));
        text->setPos(i * xPlot - 10, 8);
        i++;
    }
    i = - 1;
    while (i * xPlot >= minX - 100) {
        scene.addLine(i * xPlot, 5, i * xPlot, - 5, axisPen);
        text = scene.addText(QString::number(i * baseXPlot));
        text->setPos(i * xPlot - 12, 8);
        i--;
    }
    text = scene.addText("0");
    text->setPos(0, 0);
    // Y-axis
    i = 1;
    while (i * yPlot <= maxY + 100) {
        scene.addLine(5, i * yPlot, - 5, i * yPlot, axisPen);
        text = scene.addText(QString::number(i * baseYPlot));
        text->setPos(- 35, i * yPlot - 10);
        i++;
    }
    i = - 1;
    while (i * yPlot >= minY - 100) {
        scene.addLine(5, i * yPlot, - 5, i * yPlot, axisPen);
        text = scene.addText(QString::number(i * baseYPlot));
        text->setPos(- 37, i * yPlot - 10);
        i--;
    }
    text = scene.addText("0");
    text->setPos(- 20, 0);
}

void Wykres::setScaling(const double &scale) {
    scalingParam *= scale;
    minX *= scale;
    minY *= scale;
    maxX *= scale;
    maxY *= scale;
    plotsNumber *= scale;
}

void Wykres::updateGraph() {
    scene.clear();
    scene.update();
    for (int i = 0; i < pointList.size(); i++) {
        graphPen.setColor(graphColor[i]);
        drawGraph(i);
    }
    drawXaxis();
    drawYaxis();
    drawScale();
}

void Wykres::on_toPointButton_clicked() {
    graphType = point;
    ui->toPointButton->setEnabled(false);
    ui->toLineButton->setEnabled(true);
}

void Wykres::on_toLineButton_clicked() {
    graphType = line;
    ui->toLineButton->setEnabled(false);
    ui->toPointButton->setEnabled(true);
}

void Wykres::on_decreaseButton_clicked() {
    setScaling(0.5);
    updateGraph();
    if (scalingParam <= 0.5) ui->decreaseButton->setEnabled(false);
    if (scalingParam < 8) ui->enlargeButton->setEnabled(true);
}

void Wykres::on_enlargeButton_clicked() {
    setScaling(2);
    updateGraph();
    if (scalingParam >= 8) ui->enlargeButton->setEnabled(false);
    if (scalingParam > 0.5) ui->decreaseButton->setEnabled(true);
}

void Wykres::on_clearFieldButton_clicked() {
    scene.clear();
    scene.update();
    for (int i = 0; i < pointList.size(); i++)
        pointList[i].clear();
    pointList.clear();
    typeList.clear();
    setStartValues();
}

void Wykres::on_drawNewGraphButton_clicked() {
    generateRandomPoints();
    updateGraph();
    if (pointList.size() >= 5) ui->drawNewGraphButton->setEnabled(false);
    ui->clearFieldButton->setEnabled(true);
    ui->enlargeButton->setEnabled(true);
    ui->decreaseButton->setEnabled(true);
}
