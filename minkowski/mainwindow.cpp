#include "mainwindow.h"

#include "shape.h"

#include <QPaintEvent>
#include <QDebug>
#include <QColor>
#include <QtMath>

#include "drawable.h"

MainWindow::MainWindow()
{
    timer = new QTimer();

    auto color1 = QColor(0, 128, 255);
    auto color2 = QColor(255, 0, 0);
    auto color3 = QColor(128, 194, 255);

    // FIRST:

    n1Shape1 = Shape::makeRectangle(71, 71);
    n1Shape1->translate(50, 100);
    n1Shape1->rotate(30 * M_PI / 180);
    n1Shape1->color = color1;

    n1Shape2 = Shape::makeRectangle(21, 41);
    n1Shape2->translate(20, 20);
    n1Shape2->rotate(-20 * M_PI / 180);
    n1Shape2->color = color2;

    n1Shape3 = Shape::minkowskiSum(n1Shape1, n1Shape2);
    n1Shape3->color = color3;

    // SECOND:

    n2Shape1 = Shape::makeCircle(5000);
    n2Shape1->translate(300,150);
    n2Shape1->color = color1;

    n2Shape2 = Shape::makeCircle(140);
    n2Shape2->translate(200, 50);
    n2Shape2->color = color2;

    n2Shape3 = Shape::minkowskiSum(n2Shape1, n2Shape2);
    n2Shape3->color = color3;

    // THIRD:

    n3Shape1 = Shape::makeRectangle(80, 100);
    n3Shape1->translate(80, 300);
    n3Shape1->rotate(35 * M_PI / 180);
    n3Shape1->color = color1;

    n3Shape2 = Shape::makeCircle(500);
    n3Shape2->translate(200, 250);
    n3Shape2->color = color2;

    n3Shape3 = Shape::minkowskiSum(n3Shape1, n3Shape2);
    n3Shape3->color = color3;

    // REST:

    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));

    resize(500, 500);
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    n1Shape3->draw(this);
    n1Shape1->draw(this);
    n1Shape2->draw(this);

    n2Shape3->draw(this);
    n2Shape1->draw(this);
    n2Shape2->draw(this);

    n3Shape3->draw(this);
    n3Shape1->draw(this);
    n3Shape2->draw(this);
}

void MainWindow::loop()
{
    n1Shape2->rotate(0.1);

    update();
}
