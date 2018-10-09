#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "shape.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Shape *n1Shape1;
    Shape *n1Shape2;
    Shape *n1Shape3;

    Shape *n2Shape1;
    Shape *n2Shape2;
    Shape *n2Shape3;

    Shape *n3Shape1;
    Shape *n3Shape2;
    Shape *n3Shape3;

    QTimer *timer;

public:
    MainWindow();
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void loop();
};

#endif // MAINWINDOW_H
