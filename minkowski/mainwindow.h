#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "rectangle.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Rectangle *r1;
    Rectangle *r2;
    Rectangle *r3;

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
