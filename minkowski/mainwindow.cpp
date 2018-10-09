#include "mainwindow.h"

#include "shape.h"

#include <QPaintEvent>
#include <QDebug>
#include <QColor>

#include "drawable.h"

MainWindow::MainWindow()
{
    timer = new QTimer();

    r1 = Shape::make_rectangle(71, 71);
    r1->translate(150, 150);
    r1->rotate(0.3);
    r1->color = QColor(0, 128, 255);

    r2 = Shape::make_rectangle(21, 41);
    r2->translate(20, 20);
    r2->rotate(-0.2);
    r2->color = QColor(255, 0, 0);

    r3 = Shape::make_rectangle(71, 71);
    r3->translate(150, 150);
    r3->rotate(0.3);
    r3->minkowski_addition(r2);
    r3->color = QColor(128, 194, 255);

    c1 = Shape::make_circle(60);
    c1->translate(100, 40);
    c1->color = QColor(255, 0, 0);

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
}

void MainWindow::loop()
{
    update();
}
