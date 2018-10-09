#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QVector>
#include <QPointF>

#include "shape.h"

class World : public QObject
{
    Q_OBJECT

private:
    QVector<QPointF> processLine(QString line);

public:
    World();
    ~World();

    static Shape *parseMap(QString path);
};

#endif // WORLD_H
