#include "shape.h"

#include <QPainter>
#include <QtMath>

#define PI 3.14

Shape::Shape() : Drawable()
{
    points = QVector<QPointF>();
}

Shape::~Shape() {}

Shape *Shape::makeRectangle(int width, int height)
{
    auto shape = new Shape;

    for (double i = 0; i < width; i++)
    {
        for (double j = 0; j < height; j++)
        {
            shape->points.append(QPointF(i, j));
        }
    }

    return shape;
}

Shape *Shape::makeCircle(int diamiter)
{
    auto shape = new Shape;

    const double r = diamiter / 2;

    for (double i = -r; i < r; i++)
    {
        for (double j = -r; j < r; j++)
        {
            if ((i < qSqrt(r - qPow(j, 2))) &&
                (j < qSqrt(r - qPow(i, 2))) &&
                (r > qPow(i, 2) + qPow(j, 2)))
            {
                shape->points.append(QPointF(i, j));
            }
        }
    }

    return shape;
}

void Shape::draw(QWidget *widget)
{
    QPainter painter(widget);
    painter.setPen(color);

    for (int i = 0; i < points.size(); i++)
    {
        painter.drawPoint(points[i].x(), points[i].y());
    }
}

QPointF Shape::getCenter()
{
    auto center = QPointF(0, 0);
    for (int i = 0; i < points.size(); i++)
    {
        center += points[i];
    }
    center /= points.size();
    return center;
}

void Shape::rotate(double angle)
{
    QPointF center = getCenter();

    translate(-center.x(), -center.y());

    double cos = qCos(angle);
    double sin = qSin(angle);

    for (int i = 0; i < points.size(); i++)
    {
        points[i].setX(points[i].x() * cos - points[i].y() * sin);
        points[i].setY(points[i].x() * sin + points[i].y() * cos);
    }

    translate(center.x(), center.y());
}

void Shape::translate(double x, double y)
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].setX(points[i].x() + x);
        points[i].setY(points[i].y() + y);
    }
}

QVector<QPointF> Shape::centerVectors()
{
    auto vectors = QVector<QPointF>();
    QPointF center = getCenter();

    for (int i = 0; i < points.size(); i++)
    {
        vectors.append(QPointF(points[i] - center));
    }

    return vectors;
}

Shape *Shape::minkowskiSum(Shape *shape, Shape *over)
{
    auto result = new Shape;

    auto vectors = over->centerVectors();

    for (int i = 0; i < shape->points.size(); i++)
    {
        for (int j = 0; j < vectors.size(); j++)
        {
            result->points.append(QPointF(shape->points[i] + vectors[j]));
        }
    }

    return result;
}
