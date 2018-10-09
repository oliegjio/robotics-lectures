#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QVector>
#include <QPointF>

#include "drawable.h"

class Shape : public Drawable
{

private:
    Shape();
    ~Shape();

    QVector<QPointF> points;

    QVector<QPointF> centerVectors();

public:
    QColor color;

    static Shape *makeRectangle(int width, int height);
    static Shape *makeCircle(int radius);
    static Shape *minkowskiSum(Shape *shape, Shape *over);

    void draw(QWidget *widget);

    void rotate(double angle);
    void translate(double x, double y);

    QPointF getCenter();
};

#endif // RECTANGLE_H
