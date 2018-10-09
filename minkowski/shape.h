#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QWidget>
#include <QVector>
#include <QPair>

#include "drawable.h"

typedef QPair<int, int> Point;
typedef QVector<Point> Vector1;
typedef QVector<Vector1> Vector2;

class Rectangle : public Drawable
{
private:
    Rectangle();

    QColor color;

    Vector2 points;

public:
    Rectangle(int x, int y, int width, int height);
    ~Rectangle();

    void draw(QWidget *widget);

    void rotate(float angle);
    void translate(int x, int y);

    Point getCenter();
    Vector1 vectorsFromCenter();

    Rectangle *copy();

    static Rectangle *minkowski_addition(Rectangle *rectangle, Vector1 centerVectors);

    void setColor(QColor color);
};

#endif // RECTANGLE_H
