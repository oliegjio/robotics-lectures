#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QSet>
#include <QPoint>
#include <QPair>

#include "drawable.h"

typedef QPair<double, double> PairD;
typedef QPair<int, int> PairI;

class Shape : public Drawable
{

private:
    Shape();
    ~Shape();

    QSet<PairD*> *pointsD;
    QSet<PairI*> *pointsI;

    QSet<PairD*> *centerVectors();

public:
    QColor color;

    static Shape *makeRectangle(int width, int height);
    static Shape *makeCircle(int radius);
    static Shape *minkowskiAddition(Shape *shape, Shape *over);

    void draw(QWidget *widget);

    void rotate(double angle);
    void translate(int x, int y);

    QPoint *getCenter();
};

#endif // RECTANGLE_H
