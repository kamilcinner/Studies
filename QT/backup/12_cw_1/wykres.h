#ifndef WYKRES_H
#define WYKRES_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>
#include <QColor>
#include <QList>
#include <QRandomGenerator>
#include <QString>
#include <QDebug>

namespace Ui {
class Wykres;
}
class GraphTypeEnum {
protected:
    enum GraphType {point, line};
};

class Wykres : public QWidget, private GraphTypeEnum {
    Q_OBJECT

public:
    explicit Wykres(QWidget *parent = nullptr);
    ~Wykres();
    void addPoint(QList<QPoint> &, int x, int y);
    void generateRandomPoints();
    void drawGraph(const int &);
    void setPens();
    void drawXaxis();
    void drawYaxis();
    void drawScale();
    void setScaling(const double &);
    void updateGraph();
    void setStartValues();

private slots:
    void on_toPointButton_clicked();
    void on_toLineButton_clicked();
    void on_decreaseButton_clicked();
    void on_enlargeButton_clicked();
    void on_clearFieldButton_clicked();
    void on_drawNewGraphButton_clicked();

private:
    Ui::Wykres *ui;
    QGraphicsScene scene;
    QPen graphPen, axisPen;
    QVector<QList<QPoint>> pointList;
    QVector<GraphType> typeList;
    QVector<QColor> graphColor;
    int plotsNumber;
    double scalingParam;
    int maxY, minY, maxX, minX, baseMaxY, baseMinY, baseMaxX, baseMinX;
    GraphType graphType;
    QRandomGenerator generator;
};

#endif // WYKRES_H
