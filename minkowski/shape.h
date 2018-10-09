#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QSet>
#include <QPoint>

#include "drawable.h"

class Shape : public Drawable
{

private:
    Shape();
    ~Shape();

    QSet<QPoint*> *points;

    QSet<QPoint*> *centerVectors();

public:
    QColor color;

    static Shape *make_rectangle(int width, int height);
    static Shape *make_circle(int radius);

    void draw(QWidget *widget);

    void rotate(double angle);
    void translate(int x, int y);

    QPoint *getCenter();

    void minkowski_addition(Shape *shape);
};

#endif // RECTANGLE_H
