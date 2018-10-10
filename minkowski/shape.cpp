#include "shape.h"

#include <QPainter>
#include <QtMath>

#define PI 3.14

Shape::Shape() : Drawable()
{
    pointsD = new QSet<PairD*>;
    pointsI = new QSet<PairI*>;
}

Shape::~Shape() {}

Shape *Shape::makeRectangle(int width, int height)
{
    auto shape = new Shape;

    for (double i = 0; i < width; i++)
    {
        for (double j = 0; j < height; j++)
        {
            shape->pointsD->insert(new PairD(i, j));
        }
    }

    return shape;
}

Shape *Shape::makeCircle(int diamiter)
{
    auto shape = new Shape;

    const double radius = diamiter / 2;

    for (double i = -radius; i < radius; i++)
    {
        for (double j = -radius; j < radius; j++)
        {
            if ((i < qSqrt(radius - qPow(j, 2))) &&
                (j < qSqrt(radius - qPow(i, 2))) &&
                (radius > qPow(i, 2) + qPow(j, 2)))
            {
                shape->pointsD->insert(new PairD(i, j));
            }
        }
    }

    return shape;
}

void Shape::draw(QWidget *widget)
{
    QPainter painter(widget);
    painter.setPen(color);

    for (auto i = pointsD->begin(); i != pointsD->end(); ++i)
    {
        painter.drawPoint(static_cast<int>((*i)->first), static_cast<int>((*i)->second));
    }
}

QPoint *Shape::getCenter()
{
    int dx = 0;
    int dy = 0;
    for (auto i = pointsD->begin(); i != pointsD->end(); ++i)
    {
        dx += (*i)->first;
        dy += (*i)->second;
    }
    dx /= pointsD->size();
    dy /= pointsD->size();
    return new QPoint(dx, dy);
}

void Shape::rotate(double angle)
{
    QPoint *center = getCenter();

    translate(-center->x(), -center->y());

    double cos = qCos(angle);
    double sin = qSin(angle);

    for (auto i = pointsD->begin(); i != pointsD->end(); ++i)
    {
        (*i)->first = (*i)->first * cos - (*i)->second * sin;
        (*i)->second = (*i)->first * sin + (*i)->second * cos;
    }

    translate(center->x(), center->y());
}

void Shape::translate(int x, int y)
{
    for (auto i = pointsD->begin(); i != pointsD->end(); ++i)
    {
        (*i)->first = (*i)->first + x;
        (*i)->second = (*i)->second + y;
    }
}

QSet<PairD*> *Shape::centerVectors()
{
    auto vectors = new QSet<PairD*>;
    QPoint *center = getCenter();

    for (auto i = pointsD->begin(); i != pointsD->end(); ++i)
    {
        vectors->insert(new PairD(*(*i) - *center));
    }

    return vectors;
}

Shape *Shape::minkowskiSum(Shape *shape, Shape *over)
{
    auto result = new Shape;

    auto vectors = over->centerVectors();

    for (auto i = shape->pointsD->begin(); i != shape->pointsD->end(); ++i)
    {
        for (auto j = vectors->begin(); j != vectors->end(); ++j)
        {
            result->pointsD->insert(new QPoint(*(*i) + *(*j)));
        }
    }

    return result;
}
