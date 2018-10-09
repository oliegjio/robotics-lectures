#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QWidget>

class Drawable {

public:
    virtual ~Drawable();
    virtual void draw(QWidget *widget);
};

#endif // DRAWABLE_H
