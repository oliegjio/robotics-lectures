#include "shape.h"

#include <QPainter>
#include <QtMath>

#define PI 3.14

Shape::Shape() : Drawable()
{
    points = new QSet<QPoint*>;
}

Shape::~Shape() {}

Shape *Shape::makeRectangle(int width, int height)
{
    auto shape = new Shape;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            shape->points->insert(new QPoint(i, j));
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
                shape->points->insert(new QPoint(static_cast<int>(i), static_cast<int>(j)));
            }
        }
    }

    return shape;
}

void Shape::draw(QWidget *widget)
{
    QPainter painter(widget);
    painter.setPen(color);

    for (auto i = points->begin(); i != points->end(); ++i)
    {
        painter.drawPoint((*i)->x(), (*i)->y());
    }
}

QPoint *Shape::getCenter()
{
    int dx = 0;
    int dy = 0;
    for (auto i = points->begin(); i != points->end(); ++i)
    {
        dx += (*i)->x();
        dy += (*i)->y();
    }
    dx /= points->size();
    dy /= points->size();
    return new QPoint(dx, dy);
}

void Shape::rotate(double angle)
{
    QPoint *center = getCenter();

    translate(-center->x(), -center->y());

    double cos = qCos(angle);
    double sin = qSin(angle);

    for (auto i = points->begin(); i != points->end(); ++i)
    {
        (*i)->setX(static_cast<int>((*i)->x() * cos - (*i)->y() * sin));
        (*i)->setY(static_cast<int>((*i)->x() * sin + (*i)->y() * cos));
    }

    translate(center->x(), center->y());
}

void Shape::translate(int x, int y)
{
    for (auto i = points->begin(); i != points->end(); ++i)
    {
        (*i)->setX((*i)->x() + x);
        (*i)->setY((*i)->y() + y);
    }
}

QSet<QPoint*> *Shape::centerVectors()
{
    auto vectors = new QSet<QPoint*>;
    QPoint *center = getCenter();

    for (auto i = points->begin(); i != points->end(); ++i)
    {
        vectors->insert(new QPoint(*(*i) - *center));
    }

    return vectors;
}

Shape *Shape::minkowskiSum(Shape *shape, Shape *over)
{
    auto result = new Shape;

    auto vectors = over->centerVectors();

    for (auto i = shape->points->begin(); i != shape->points->end(); ++i)
    {
        for (auto j = vectors->begin(); j != vectors->end(); ++j)
        {
            result->points->insert(new QPoint(*(*i) + *(*j)));
        }
    }

    return result;
}
