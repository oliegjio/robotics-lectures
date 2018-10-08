#include "rectangle.h"

#include <QDebug>
#include <QPainter>
#include <QtMath>

Rectangle::Rectangle(int x, int y, int width, int height) : Drawable()
{
    for (int i = 0; i < width; i++)
    {
        points.append(Vector1());
        for (int j = 0; j < height; j++)
        {
            points[i].append(Point(i + x, j + y));
        }
    }
}

Rectangle::Rectangle() {}

Rectangle::~Rectangle() {}

void Rectangle::setColor(QColor color) { this->color = color; }

void Rectangle::draw(QWidget *widget)
{
    QPainter painter(widget);
    painter.setPen(color);

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = 0; j < points.last().size(); j++)
        {
            Point point = points[i][j];
            painter.drawPoint(point.first, point.second);
        }
    }
}

Point Rectangle::getCenter()
{
    int x1 = (points[0][0].first + points.last().last().first) / 2;
    int y1 = (points[0][0].second + points.last().last().second) / 2;
    int x2 = (points[0].last().first + points.last()[0].first) / 2;
    int y2 = (points[0].last().second + points.last()[0].second) / 2;
    return Point((x1 + x2) / 2, (y1 + y2) / 2);
}

void Rectangle::rotate(float angle)
{
    Point center = getCenter();

    translate(-center.first, -center.second);

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = 0; j < points.last().size(); j++)
        {
            points[i][j].first = points[i][j].first * qCos(angle) - points[i][j].second * qSin(angle);
            points[i][j].second = points[i][j].first * qSin(angle) + points[i][j].second * qCos(angle);
        }
    }

    translate(center.first, center.second);
}

void Rectangle::translate(int x, int y)
{
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = 0; j < points.last().size(); j++)
        {
            points[i][j].first += x;
            points[i][j].second += y;
        }
    }
}

Vector1 Rectangle::vectorsFromCenter()
{
    Vector1 vectors;
    Point center = getCenter();

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = 0; j < points.last().size(); j++)
        {
            vectors.append(Point(points[i][j].first - center.first, points[i][j].second - center.second));
        }
    }

    return vectors;
}

Rectangle *Rectangle::copy()
{
    Rectangle *rectangle = new Rectangle();
    for (int i = 0 ; i < points.size(); i++) {
        rectangle->points.append(Vector1());
        for (int j = 0; j < points.last().size(); j++)
        {
            rectangle->points[i].append(points[i][j]);
        }
    }
    return rectangle;
}

Rectangle* Rectangle::minkowski_addition(Rectangle *rectangle, Vector1 centerVectors)
{
    Rectangle *result = rectangle->copy();

    for (int i = 0; i < rectangle->points.last().size(); i++)
    {
        for (int j = 0; j < centerVectors.size(); j++)
        {
            int x = centerVectors[j].first + rectangle->points[0][i].first;
            int y = centerVectors[j].second + rectangle->points[0][i].second;
            result->points[i].append(Point(x, y));
        }
    }

    for (int i = 0; i < rectangle->points.size(); i++)
    {
        for (int j = 0; j < centerVectors.size(); j++)
        {
            int x = centerVectors[j].first + rectangle->points[i][0].first;
            int y = centerVectors[j].second + rectangle->points[i][0].second;
            result->points[i].append(Point(x, y));
        }
    }

    for (int i = 0; i < rectangle->points.size(); i++)
    {
        for (int j = 0; j < centerVectors.size(); j++)
        {
            int x = centerVectors[j].first + rectangle->points[i].last().first;
            int y = centerVectors[j].second + rectangle->points[i].last().second;
            result->points[i].append(Point(x, y));
        }
    }

    for (int i = 0; i < rectangle->points.last().size(); i++)
    {
        for (int j = 0; j < centerVectors.size(); j++)
        {
            int x = centerVectors[j].first + rectangle->points.last()[i].first;
            int y = centerVectors[j].second + rectangle->points.last()[i].second;
            result->points[i].append(Point(x, y));
        }
    }

    return result;
}
