#include "mainwindow.h"

#include "rectangle.h"

#include <QPaintEvent>
#include <QDebug>
#include <QColor>

#include "drawable.h"

MainWindow::MainWindow()
{
    timer = new QTimer();

    r1 = new Rectangle(150, 150, 71, 71);
    r1->setColor(QColor(255, 0, 0));
    r1->rotate(0.3);

    r2 = new Rectangle(50, 50, 21, 41);
    r2->setColor(QColor(0, 255, 0));
    r2->rotate(-0.2);

    r3 = Rectangle::minkowski_addition(r1, r2->vectorsFromCenter());
    r3->setColor(QColor(0, 0, 255));

    timer->setInterval(100);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));

    resize(400, 400);
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *event)
{
    r3->draw(this);
    r1->draw(this);
    r2->draw(this);
}

void MainWindow::loop()
{
    update();
}
