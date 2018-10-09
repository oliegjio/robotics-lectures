#include "shape.h"

#include <QPainter>
#include <QtMath>

Shape::Shape() : Drawable() {}

Shape::~Shape() {}

Shape *Shape::make_rectangle(int width, int height)
{
    auto shape = new Shape;
    shape->points = new QSet<QPoint*>;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            shape->points->insert(new QPoint(i, j));
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

void Shape::minkowski_addition(Shape *shape)
{
    auto vectors = shape->centerVectors();

    auto oldPoints = new QSet<QPoint*>(*points);
    points->clear();

    for (auto i = oldPoints->begin(); i != oldPoints->end(); ++i)
    {
        for (auto j = vectors->begin(); j != vectors->end(); ++j)
        {
            points->insert(new QPoint(*(*i) + *(*j)));
        }
    }
}
