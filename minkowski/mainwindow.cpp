#include "mainwindow.h"

#include "shape.h"

#include <QPaintEvent>
#include <QDebug>
#include <QColor>

#include "drawable.h"

MainWindow::MainWindow()
{
    timer = new QTimer();

    // FIRST:

    r1 = Shape::make_rectangle(71, 71);
    r1->translate(50, 100);
    r1->rotate(0.3);
    r1->color = QColor(0, 128, 255);

    r2 = Shape::make_rectangle(21, 41);
    r2->translate(20, 20);
    r2->rotate(-0.2);
    r2->color = QColor(255, 0, 0);

    r3 = Shape::minkowski_addition(r1, r2);
    r3->color = QColor(128, 194, 255);

    // SECOND:

    c1 = Shape::make_circle(201);
    c1->translate(350, 200);
    c1->color = QColor(255, 0, 0);

    c2 = Shape::make_circle(71);
    c2->translate(200, 50);
    c2->color = QColor(0, 255, 0);

    // REST:

    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));

    resize(400, 400);
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    r3->draw(this);
    r1->draw(this);
    r2->draw(this);

    c1->draw(this);
    c2->draw(this);
}

void MainWindow::loop()
{
    update();
}
