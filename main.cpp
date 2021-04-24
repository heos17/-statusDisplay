#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <unistd.h>

#include <wiringPi.h>

MainWindow *ptWindow;

void setInterrupt(MainWindow *pt);
void interrupt();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

     setInterrupt(&w);




    return a.exec();
}

void setInterrupt(MainWindow *pt)
{
    ptWindow = pt;

    wiringPiISR(29,INT_EDGE_BOTH, &interrupt);

}

void interrupt()
{
    ptWindow->interrupt();
}
