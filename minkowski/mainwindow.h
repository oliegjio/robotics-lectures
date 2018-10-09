#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "shape.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Shape *r1;
    Shape *r2;
    Shape *r3;

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
