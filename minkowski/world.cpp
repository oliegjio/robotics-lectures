#include "world.h"

#include <QFile>
#include <QTextStream>

World::World() : QObject() {}

World::~World() {}

Shape *World::parseMap(QString path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    auto shape =  new Shape;

    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        auto data = processLine(line);
        shape->points += data;
    }

    return shape;
}

QVector<QPointF> processLine(QString line)
{
    if (line[0] == 'r')
    {

    }
}
